/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:13:10 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:13:33 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_fds(t_mini *data, int *stdin_copy, int *stdout_copy)
{
	if (data->process[0].fd_input > -1)
	{
		*stdin_copy = dup(STDIN_FILENO);
		dup2(data->process[0].fd_input, STDIN_FILENO);
		close(data->process[0].fd_input);
		data->process[0].fd_input = -1;
	}
	if (data->process[0].fd_output > -1)
	{
		*stdout_copy = dup(STDOUT_FILENO);
		dup2(data->process[0].fd_output, STDOUT_FILENO);
		close(data->process[0].fd_output);
		data->process[0].fd_output = -1;
	}
}
