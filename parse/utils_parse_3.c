/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:20:09 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:20:14 by srituit          ###   ########.fr       */
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
