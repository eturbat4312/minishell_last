/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:05:34 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 12:06:05 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_redir(t_process *process)
{
	size_t	i;

	i = 0;
	while (i < process->redirs.lenght / 2)
	{
		if (process->redirs.elements[i * 2 + 1])
			if (all_space(process->redirs.elements[i * 2 + 1]))
				return (0);
			i++;
	}
	return (1);
}

char	**split(char *s, char delimiter)
{
	int		i;
	int		j;
	int		pos;
	char	**result;

	result = new_memory(MAX_ALLOC * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		pos = locate_char(&s[i], delimiter);
		if (pos == -1)
		{
			result[j++] = ft_strdup(&s[i]);
			break ;
		}
		if (pos == 0)
		{
			ft_free_tab(result);
			return (0);
		}
		result[j++] = ft_substr(&s[i], 0, pos);
		i += pos + 1;
	}
	return (result);
}

int	locate_char(char *s, char delimiter)
{
	char	delimiters[2];

	delimiters[0] = delimiter;
	delimiters[1] = 0;
	return (locate_chars(s, delimiters));
}
