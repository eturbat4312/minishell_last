/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:00:11 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:01:21 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	option_n(char **complete_cmd, int *index)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (complete_cmd[i])
	{
		*index = i;
		if (ft_strnstr(complete_cmd[i], "-n", 2))
		{
			newline = 0;
			if (!ft_strfind('n', &complete_cmd[i][1]))
			{
				if (i == 1)
					newline = 1;
				return (newline);
			}
		}
		else
			return (newline);
		i++;
	}
	return (newline);
}

void	ft_echo(char **complete_cmd)
{
	int	i;
	int	newline;
	int	save_index;

	if (complete_cmd[1])
	{
		newline = option_n(complete_cmd, &i);
		save_index = i;
		while (complete_cmd[i])
		{
			if (check_cases(complete_cmd, i, newline, save_index) == -1)
				return ;
			i++;
		}
	}
	else
	{
		if (!special_putstr("\n", STDOUT_FILENO))
		{
			perror("minishell: echo: write error");
			g_exit_status = 1;
			return ;
		}
	}
	g_exit_status = 0;
}
