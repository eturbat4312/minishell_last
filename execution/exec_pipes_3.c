/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:29:10 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 14:29:28 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_process(t_mini *mini, t_elements *elements, int i)
{
	if (mini->process[i].fd_input > -1)
		dup2(mini->process[i].fd_input, 0);
	if (mini->process[i].fd_output > -1)
		dup2(mini->process[i].fd_output, 1);
	else
		dup2(elements->pipe_fd[i][1], 1);
}

void	middle_process(t_mini *data, t_elements *elements, int i)
{
	if (data->process[i].fd_input > -1)
		dup2(data->process[i].fd_input, 0);
	else
		dup2(elements->pipe_fd[i - 1][0], 0);
	if (data->process[i].fd_output > -1)
		dup2(data->process[i].fd_output, 1);
	else
		dup2(elements->pipe_fd[i][1], 1);
}

void	last_process(t_mini *mini, t_elements *elements, int i)
{
	if (mini->process[i].fd_input > -1)
		dup2(mini->process[i].fd_input, 0);
	else
		dup2(elements->pipe_fd[i - 1][0], 0);
	if (mini->process[i].fd_output > -1)
		dup2(mini->process[i].fd_output, 1);
}
