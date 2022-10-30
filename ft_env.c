/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:15:49 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:16:24 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_write(char *my_var)
{
	errno = 0;
	if (!special_putend(my_var, STDOUT_FILENO))
	{
		perror("env: write error");
		if (errno == ENOSPC)
			g_exit_status = 125;
		else
			g_exit_status = 1;
		return (0);
	}
	return (1);
}

void	ft_env(char **complete_cmd, char **env)
{
	int	i;

	i = 0;
	if (complete_cmd[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n,", STDERR_FILENO);
		g_exit_status = 1;
		return ;
	}
	if (env)
	{
		while (env[i])
		{
			if (!check_write(env[i]))
				return ;
			i++;
		}
	}
	g_exit_status = 0;
}
