/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:47:33 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 15:47:48 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

void	copy_then_free(char *src, int *i, char *dst)
{
	int	j;

	j = 0;
	while (dst[j])
		src[(*i)++] = dst[j++];
	free(dst);
}

char	*active_env(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			s[i] = '$';
		i++;
	}
	return (s);
}

char	*deactive_env(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			s[i] = 1;
		i++;
	}
	return (s);
}
