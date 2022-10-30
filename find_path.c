/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:13:45 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:14:32 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path(char **env)
{
	char	*path_env;
	char	**full_path;

	path_env = my_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	full_path = ft_split(path_env, ':');
	if (!full_path)
	{
		perror("minishell: Malloc failure");
		ft_free_tab(env);
		exit(2);
	}
	return (full_path);
}
