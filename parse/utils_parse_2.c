/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:18:20 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:19:07 by srituit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_data_s(char **tmp, t_mini *data)
{
	free_processes(data);
	ft_free_tab(tmp);
	return (0);
}

int	count_elements(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_all_space(char **tmp)
{
	int	i;

	if (!tmp)
	{
		error_fct3("unexpected token ", "|'\n", 2);
		return (0);
	}
	i = 0;
	while (tmp[i])
	{
		if (all_space(tmp[i]))
		{
			ft_free_tab(tmp);
			error_fct3("unexpected token ", "|'\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_processes(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->nb_processes)
	{
		free_process(mini, i);
		i++;
	}
	free(mini->process);
	mini->process = NULL;
}
