/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:03:32 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 12:03:50 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_process(int sig)
{
	if (sig == SIGINT)
		write(1, "^a\n", 3);
	if (sig == SIGQUIT)
		write(1, "^\\Quit: 3\n", 10);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signals(struct termios *save)
{
	struct termios	new;

	tcgetattr(STDIN_FILENO, save);
	new = *save;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
}
