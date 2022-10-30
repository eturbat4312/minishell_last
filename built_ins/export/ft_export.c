/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:37:04 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:43:14 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_err(char *cmd)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int	check_empty(char *param)
{
	if (!param || !ft_strcmp(param, ""))
		return (1);
	else
		return (0);
}

void	export_set_env(char *cmd, t_mini *mini)
{
	int	pos;

	pos = check_env_ex(cmd);
	if (!pos)
	{
		print_err(cmd);
		g_exit_status = 1;
		return ;
	}
	if (pos > 0)
		add_env(cmd, mini, pos);
}

void	ft_export(char **cmd, t_mini *mini)
{
	int	i;
	int	non_empty_args;

	g_exit_status = 0;
	non_empty_args = 0;
	i = 1;
	if (!check_empty(cmd[1]))
	{
		while (cmd[i])
		{
			non_empty_args++;
			export_set_env(cmd[i], mini);
			i++;
		}
	}
	if (!non_empty_args)
		sort_print(mini);
}
