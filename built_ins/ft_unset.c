/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:35:25 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:36:33 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env(char *s)
{
	int	i;

	if (!((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a'
				&& s[0] <= 'z') || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	remove_env(char *var, t_mini *data)
{
	int	i;
	int	size;
	int	var_len;

	size = count_elements((void **)data->env);
	i = 0;
	var_len = ft_strlen(var);
	if (data->env)
	{
		while (data->env[i])
		{
			if (ft_strnstr(data->env[i], var, var_len)
				&& data->env[i][var_len] == '=')
			{
				free(data->env[i]);
				data->env[i] = data->env[size - 1];
				data->env[size - 1] = NULL;
				return ;
			}
			i++;
		}
	}
}

void	ft_unset(char **cmd, t_mini *data)
{
	int	i;

	g_exit_status = 0;
	if (!cmd[1])
		return ;
	i = 1;
	while (cmd[i])
	{
		if (!check_env(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			i++;
			continue ;
		}
		remove_env(cmd[i], data);
		i++;
	}
}
