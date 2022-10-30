/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:01:38 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:08:19 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	case3(char *arg)
{
	if (!special_mtp_putstr(arg, " ", NULL, STDOUT_FILENO))
	{
		perror("minishell: echo: write error");
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	case2(char *arg)
{
	if (!special_putstr(arg, STDOUT_FILENO))
	{
		perror("minishell: echo: write error");
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	case1(char *arg)
{
	if (!special_putend(arg, STDOUT_FILENO))
	{
		perror("minishell: echo: write error");
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	check_cases(char **complete_cmd, int i, int newline, int save_index)
{
	if (newline && !complete_cmd[i + 1])
	{
		if (case1(complete_cmd[i]) == -1)
			return (-1);
	}
	else if (!newline && !complete_cmd[i + 1]
		&& ft_strfind('n', &complete_cmd[i][1])
		&& complete_cmd[i][0] == '-' && i == save_index)
		return (0);
	else if (!newline && !complete_cmd[i + 1])
	{
		if (case2(complete_cmd[i]) == -1)
			return (-1);
	}
	else
	{
		if (case3(complete_cmd[i]) == -1)
			return (-1);
	}
	return (0);
}
