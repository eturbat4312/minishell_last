/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:17:59 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:18:57 by srituit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*scan_double_quoted(char *s, int *i)
{
	int		j;
	char	*result;

	result = new_string(ft_strlen(s));
	(*i)++;
	j = 0;
	while (s[*i])
	{
		if (s[*i] == '"')
		{
			(*i)++;
			return (result);
		}
		result[j++] = s[(*i)++];
	}
	free (result);
	return (NULL);
}

char	*scan_single_quoted(char *s, int *i)
{
	int		j;
	char	*result;

	result = new_string(ft_strlen(s));
	(*i)++;
	j = 0;
	while (s[*i])
	{
		if (s[*i] == '\'')
		{
			(*i)++;
			return (result);
		}
		result[j++] = s[(*i)++];
	}
	free(result);
	return (NULL);
}

char	*scan_unquoted(char *s, int *i)
{
	int		j;
	char	*result;

	result = new_string(ft_strlen(s));
	j = 0;
	while (s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '"')
			return (result);
		result[j++] = s[(*i)++];
	}
	return (result);
}

char	*new_string(int capacity)
{
	char	*result;

	capacity += 1;
	result = (char *)my_malloc(capacity * sizeof(char));
	ft_memset(result, 0, capacity * sizeof(char));
	return (result);
}
