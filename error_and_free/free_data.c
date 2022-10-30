/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:54:50 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:55:50 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_mini *mini)
{
	int	i;

	i = 0;
	ft_free_tab(mini->path);
	mini->separated_line = NULL;
	ft_free_tab(mini->env);
	mini->env = NULL;
	free(mini->line);
	mini->line = NULL;
	if (mini->process)
	{
		close_redirection_fds(mini);
		free_processes(mini);
	}
	rl_clear_history();
}
