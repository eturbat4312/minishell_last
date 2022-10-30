/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:20:41 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 14:27:57 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_built_in(t_mini *mini, t_elements *elements, int i)
{
	if (elements->built_in[i] == 1)
		ft_echo(mini->process[i].params);
	else if (elements->built_in[i] == 2)
		ft_env(mini->process[0].params, mini->env);
	else if (elements->built_in[i] == 3)
		ft_pwd(mini->env);
	else if (elements->built_in[i] == 4)
		ft_cd(mini->process[i].params, mini);
	else if (elements->built_in[i] == 5)
		ft_export(mini->process[i].params, mini);
	else if (elements->built_in[i] == 6)
		ft_unset(mini->process[i].params, mini);
	else if (elements->built_in[i] == 7)
		ft_exit(mini->process[i].params, mini);
}

static void	exec_childs(t_mini *mini, t_elements *elements, int nb_pipes, int i)
{
	if (!i)
		first_process(mini, elements, i);
	else if (i == nb_pipes)
		last_process(mini, elements, i);
	else
		middle_process(mini, elements, i);
	close_fds(mini, elements->pipe_fd, nb_pipes);
	close_redirection_fds(mini);
	if (elements->built_in[i])
		exec_built_in(mini, elements, i);
	else if (mini->process[i].params && mini->process[i].params[0])
	{
		if (execve(mini->process[i].params[0],
				mini->process[i].params, mini->env) == -1)
			error_fct(mini, "minishell: Execve failure", 7);
	}
	free_elements(elements, nb_pipes);
	free_data(mini);
	exit(g_exit_status);
}

void	wait_for_childs(t_mini *data, t_elements *elements, int nb_pipes)
{
	int	x;
	int	count;
	int	status;

	x = 0;
	count = 0;
	data->sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &data->sigint, NULL);
	while (x <= nb_pipes)
	{
		waitpid(elements->child[x], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_exit_status = WTERMSIG(status) + 128;
			if (g_exit_status == 130 && !count)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (g_exit_status == 131 && !count)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			count++;
		}
		x++;
	}
}

void	exec_processes(t_mini *mini, t_elements *elements, int nb_pipes)
{
	int					i;
	struct sigaction	child_sigquit;

	i = 0;
	ft_memset(&child_sigquit, 0, sizeof(struct sigaction));
	while (i <= nb_pipes)
	{
		elements->child[i] = fork();
		if (elements->child[i] == -1)
			error_fct(mini, "minishell: Fork failure", 6);
		if (!elements->child[i])
		{
			child_sigquit.sa_handler = &child_sigquit_handler;
			sigaction(SIGQUIT, &child_sigquit, NULL);
			exec_childs(mini, elements, nb_pipes, i);
		}
		i++;
	}
	close_fds(mini, elements->pipe_fd, nb_pipes);
	close_redirection_fds(mini);
	wait_for_childs(mini, elements, nb_pipes);
}

void	exec_pipes(t_mini *mini, int nb_pipes)
{
	t_elements	elements;

	ft_memset(&elements, 0, sizeof(t_elements));
	malloc_elements(mini, &elements, nb_pipes);
	check_all_cmds(mini, &elements, nb_pipes);
	exec_processes(mini, &elements, nb_pipes);
	mini->sigint.sa_handler = &main_sigint_handler;
	sigaction(SIGINT, &mini->sigint, NULL);
	free_elements(&elements, nb_pipes);
}
