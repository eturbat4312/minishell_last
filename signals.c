/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:59:29 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 12:02:49 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(t_mini *data)
{
	ft_memset(&data->sigint, 0, sizeof(struct sigaction));
	data->sigint.sa_handler = &main_sigint_handler;
	sigaction(SIGINT, &data->sigint, NULL);
	ft_memset(&data->sigquit, 0, sizeof(struct sigaction));
	data->sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->sigquit, NULL);
}

void	end_heredoc(char *end)
{
	char	*wanted_end;

	wanted_end = ft_mtp_strjoin("(wanted `", end, "\')");
	if (wanted_end)
	{
		ft_mtp_putendl_fd(STDERR_FILENO,
			"minishell: warning: here-document delimited by end-of-file ",
			wanted_end, NULL);
		free(wanted_end);
	}
}

void	main_sigint_handler(int signum)
{
	g_exit_status = signum + 128;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("\0", 1);
	rl_redisplay();
}

void	child_sigquit_handler(int signum)
{
	g_exit_status = signum;
	exit(g_exit_status);
}
