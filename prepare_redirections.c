/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:58:45 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 11:59:16 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redirection_fds(t_mini *data)
{
	int	i;

	i = 0;
	while (i < data->nb_processes)
	{
		if (data->process[i].fd_input > -1)
		{
			close(data->process[i].fd_input);
			data->process[i].fd_input = -1;
		}
		if (data->process[i].fd_output > -1)
		{
			close(data->process[i].fd_output);
			data->process[i].fd_output = -1;
		}
		i++;
	}
}

void	prepare_redirections(t_mini *data)
{
	int	i;

	i = 0;
	while (i < data->nb_processes)
	{
		if (!prepare_redirs(data, i))
			data->process[i].error = true;
		i++;
	}
}
