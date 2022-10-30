/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:19:17 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:19:22 by srituit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_char_in(char ch, char *delimiters)
{
	while (*delimiters)
	{
		if (ch == *delimiters)
			return (true);
		delimiters++;
	}
	return (false);
}

char	check_open(char open, char c)
{
	if (open == 0)
		open = c;
	else if (open == c)
		open = 0;
	return (open);
}

int	locate_chars(char *s, char *delimiters)
{
	int		i;
	char	open;

	i = 0;
	open = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			open = check_open(open, s[i]);
		else if (open == 0 && is_char_in(s[i], delimiters))
			return (i);
		i++;
	}
	return (-1);
}
