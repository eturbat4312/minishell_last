/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:18:57 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 14:20:25 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_fds(int stdin_copy, int stdout_copy)
{
	if (stdin_copy > -1)
	{
		dup2(stdin_copy, STDIN_FILENO);
		close(stdin_copy);
	}
	if (stdout_copy > -1)
	{
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
	}
}

static void	exec_child(int child, int *status, t_mini *data)
{
	struct sigaction	child_sigquit;

	ft_memset(&child_sigquit, 0, sizeof(struct sigaction));
	if (!child)
	{
		child_sigquit.sa_handler = &child_sigquit_handler;
		sigaction(SIGQUIT, &child_sigquit, NULL);
		close_redirection_fds(data);
		if (data->process[0].params)
		{
			if (execve(data->process[0].params[0], data->process[0].params,
					data->env) == -1)
				error_fct(data, "minishell: Execve failure", 7);
		}
		free_data(data);
		exit(g_exit_status);
	}
	data->sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &data->sigint, NULL);
	waitpid(child, status, 0);
	data->sigint.sa_handler = &main_sigint_handler;
	sigaction(SIGINT, &data->sigint, NULL);
}

void	exec_no_built_in(t_mini *data)
{
	int	child;
	int	status;

	data->process[0].params = find_cmds(data->process[0].params, data);
	if (!data->process[0].params)
		return ;
	child = fork();
	if (child == -1)
		error_fct(data, "minishell: Fork Failure", 6);
	exec_child(child, &status, data);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = WTERMSIG(status) + 128;
		if (g_exit_status == 130)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (g_exit_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

static void	exec_built_in(int built_in, t_mini *mini)
{
	if (built_in == 1)
		ft_echo(mini->process[0].params);
	else if (built_in == 2)
		ft_env(mini->process[0].params, mini->env);
	else if (built_in == 3)
		ft_pwd(mini->env);
	else if (built_in == 4)
		ft_cd(mini->process[0].params, mini);
	else if (built_in == 5)
		ft_export(mini->process[0].params, mini);
	else if (built_in == 6)
		ft_unset(mini->process[0].params, mini);
	else if (built_in == 7)
		ft_exit(mini->process[0].params, mini);
}

void	exec_cmds(t_mini *mini)
{
	int	built_in;
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = -1;
	stdout_copy = -1;
	if (!mini->process[0].params[0])
	{
		close_redirection_fds(mini);
		return ;
	}
	dup_fds(mini, &stdin_copy, &stdout_copy);
	built_in = find_built_ins(mini->process[0].params[0]);
	if (built_in)
		exec_built_in(built_in, mini);
	else
	{
		exec_no_built_in(mini);
	}
	restore_fds(stdin_copy, stdout_copy);
	close_redirection_fds(mini);
}
