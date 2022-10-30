/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:46:02 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:47:02 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_fct(t_mini *mini, char *msg, int exit_value)
{
	if (msg)
		perror(msg);
	if (mini)
		free_data(mini);
	exit(exit_value);
}

void	*my_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (!result)
		exit (2);
	return (result);
}

void	error_fct2(char *msg, int exit_value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = exit_value;
}

void	error_fct3(char *msg, char *err_str, int exit_value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(err_str, 2);
	g_exit_status = exit_value;
}
