/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:02:52 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:06:09 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_value(t_mini *data, char *var, char *new_value)
{
	int		i;
	char	*tmp;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
		{
			if (!ft_strnstr(data->env[i], var, ft_strlen(var)))
				i++;
			else
			{
				tmp = ft_mtp_strjoin(var, "=", new_value);
				if (!tmp)
					error_fct(data, "minishell: Malloc failure", 2);
				free(data->env[i]);
				data->env[i] = tmp;
				return ;
			}
		}
	}
}
