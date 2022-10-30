/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:15:54 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 16:16:36 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_redir(char *s)
{
	size_t	size;

	size = ft_strlen(s);
	if ((s[size - 1] == '<' || s[size - 1] == '>') && s[size] == '\0')
		return (true);
	return (false);
}

void	remove_faulty_processes(t_mini *data)
{
	int	i;
	int	pos;

	i = 0;
	pos = -1;
	while (i < data->nb_processes)
	{
		if (data->process[i].error)
			pos = i;
		i++;
	}
	if (pos == -1)
		return ;
	i = 0;
	while (i <= pos)
		free_process(data, i++);
	i = pos + 1;
	while (i < data->nb_processes)
	{
		data->process[i - pos - 1] = data->process[i];
		init_process(&data->process[i]);
		i++;
	}
	data->nb_processes -= pos + 1;
}

bool	all_space(char *s)
{
	bool	ret;
	int		i;

	ret = false;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}
