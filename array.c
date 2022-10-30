/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:01:55 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:02:37 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array	new_array(void)
{
	t_array	result;

	result.lenght = 0;
	result.capacity = 0;
	result.elements = NULL;
	return (result);
}

void	array_stretch(t_array *arr)
{
	size_t	new_capacity;
	void	**new_elements;
	size_t	i;

	new_capacity = arr->capacity * 2 + 1;
	new_elements = my_malloc(new_capacity * sizeof(void *));
	i = 0;
	while (i < arr->lenght)
	{
		new_elements[i] = arr->elements[i];
		i++;
	}
	if (arr->elements)
		free(arr->elements);
	arr->capacity = new_capacity;
	arr->elements = new_elements;
}

void	array_append(t_array *arr, void *new_element)
{
	if (arr->lenght + 1 > arr->capacity)
		array_stretch(arr);
	arr->elements[arr->lenght] = new_element;
	arr->lenght++;
}

void	delete_array(t_array *arr)
{
	arr->lenght = 0;
	arr->capacity = 0;
	if (arr->elements)
	{
		free(arr->elements);
		arr->elements = NULL;
	}
}
