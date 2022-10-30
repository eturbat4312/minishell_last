/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:29:38 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 14:29:52 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_built_ins(char *cmd)
{
	if (!ft_strncmp(cmd, "echo\0", 5))
		return (1);
	if (!ft_strncmp(cmd, "env\0", 4))
		return (2);
	if (!ft_strncmp(cmd, "pwd\0", 4))
		return (3);
	if (!ft_strncmp(cmd, "cd\0", 3))
		return (4);
	if (!ft_strncmp(cmd, "export\0", 7))
		return (5);
	if (!ft_strncmp(cmd, "unset\0", 6))
		return (6);
	if (!ft_strncmp(cmd, "exit\0", 5))
		return (7);
	return (0);
}
