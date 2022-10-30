/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:39:19 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 15:39:29 by eturbat          ###   ########.fr       */
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
