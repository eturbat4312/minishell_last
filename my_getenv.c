/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:23:20 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:23:25 by srituit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *name, char **my_envp)
{
	int	i;

	i = 0;
	if (!my_envp)
		return (NULL);
	while (my_envp[i])
	{
		if (ft_strnstr(my_envp[i], name, ft_strlen(name))
			&& my_envp[i][ft_strlen(name)] == '=')
			return (&(my_envp[i][ft_strlen(name) + 1]));
		else
			i++;
	}
	return (NULL);
}
