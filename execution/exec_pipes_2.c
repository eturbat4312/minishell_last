/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:28:09 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 14:28:58 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_mini *mini, int **pipe_fd, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (close(pipe_fd[i][0]) == -1)
			error_fct(mini, "minishell: Close fd failuuure", 9);
		if (close(pipe_fd[i][1]) == -1)
			error_fct(mini, "minishell: Close fd failure", 9);
		i++;
	}
}

void	malloc_elements(t_mini *mini, t_elements *elements, int nb_pipes)
{
	int	i;

	i = 0;
	elements->child = malloc(sizeof(int) * (nb_pipes + 1));
	if (!elements->child)
		error_fct(mini, "minishell: Malloc failure", 2);
	elements->built_in = malloc(sizeof(int) * (nb_pipes + 1));
	if (!elements->built_in)
		error_fct(mini, "minishell: Malloc failure", 2);
	elements->pipe_fd = malloc(sizeof(int *) * nb_pipes);
	if (!elements->pipe_fd)
		error_fct(mini, "minishell: Malloc failure", 2);
	while (i < nb_pipes)
	{
		elements->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!elements->pipe_fd)
			error_fct(mini, "minishell: Malloc failure", 2);
		if (pipe(elements->pipe_fd[i]) == -1)
		{
			close_fds(mini, elements->pipe_fd, i);
			error_fct(mini, "minishell: Pipe failure", 5);
		}
		i++;
	}
}

void	check_all_cmds(t_mini *mini, t_elements *elements, int nb_pipes)
{
	int	i;

	i = 0;
	while (i <= nb_pipes)
	{
		if (!mini->process[i].params[0])
		{
			elements->built_in[i] = 0;
			i++;
			continue ;
		}
		elements->built_in[i] = find_built_ins(mini->process[i].params[0]);
		if (!elements->built_in[i])
			mini->process[i].params = find_cmds(mini->process[i].params, mini);
		i++;
	}
}

void	free_elements(t_elements *elements, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		free(elements->pipe_fd[i]);
		i++;
	}
	free(elements->pipe_fd);
	free(elements->built_in);
	free(elements->child);
}
