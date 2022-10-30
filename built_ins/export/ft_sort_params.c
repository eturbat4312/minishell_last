/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:43:30 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:44:13 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_params(char **tab, int size)
{
	int	i;
	int	j;
	int	min_index;

	i = 0;
	while (i < size)
	{
		min_index = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[j], tab[min_index]) <= 0)
			{
				min_index = j;
			}
			j++;
		}
		ft_swap(&tab[i], &tab[min_index]);
		i++;
	}
}
