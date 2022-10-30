/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:34:18 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 15:37:53 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*new_memory(size_t size)
{
	void	*result;

	result = my_malloc(size);
	ft_memset(result, 0, size);
	return (result);
}

int	parse_param(char *s, int pos, char **process, t_mini *mini)
{
	int	next_pos;

	next_pos = pos + 1 + locate_chars(&s[pos + 1], "<> ");
	if (next_pos < pos + 1)
		next_pos = ft_strlen(s);
	if (next_pos - pos > 1)
	{
		*process = eval(ft_substr(s, pos + 1, next_pos - pos - 1), mini);
		if (!*process)
			return (-1);
	}
	return (next_pos);
}

bool	parse_process(char *s, t_process *process, t_mini *mini)
{
	int	j;
	int	pos;

	pos = -1;
	process->params = new_memory(MAX_ALLOC * sizeof(char *));
	j = 0;
	while (pos + 1 < (int)ft_strlen(s))
	{
		if (pos >= 0 && is_char_in(s[pos], "<>"))
		{
			pos = parse_redirection(s, pos, process, mini);
			continue ;
		}
		pos = parse_param(s, pos, &process->params[j], mini);
		if (pos < 0)
			return (false);
		if (process->params[j])
			j++;
	}
	return (true);
}
