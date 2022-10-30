/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:07:19 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:12:57 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_env(char *envp[])
{
	int		i;
	char	**my_envp;

	i = 0;
	my_envp = malloc(sizeof(char *) * (ft_tab_len(envp) + 1));
	if (!my_envp)
		return (NULL);
	if (my_envp)
	{
		while (envp[i])
		{
			my_envp[i] = ft_strdup(envp[i]);
			i++;
		}
	}
	my_envp[i] = NULL;
	return (my_envp);
}
