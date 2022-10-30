/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:34:29 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 11:53:29 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_minishell(t_mini *mini)
{
	while (1)
	{
		mini->line = readline("tory_sacha_minishell> ");
		if (mini->line && *mini->line)
		{
			add_history(mini->line);
			parse(mini);
			free(mini->line);
			mini->line = NULL;
		}
		else if (mini->line && !*mini->line)
		{
			free(mini->line);
			mini->line = NULL;
		}
		else if (!mini->line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	save;
	t_mini			mini;

	(void) argv;
	ft_signals(&save);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (argc != 1)
		return (1);
	g_exit_status = 0;
	ft_memset(&mini, 0, sizeof(t_mini));
	mini.process = NULL;
	mini.env = dup_env(envp);
	mini.path = find_path(mini.env);
	start_minishell(&mini);
	free_data(&mini);
	return (g_exit_status);
}
