/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtp_putendl_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:22:16 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:23:19 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mtp_putendl_fd(int fd, char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, fd);
	if (s2)
		ft_putstr_fd(s2, fd);
	if (s3)
		ft_putstr_fd(s3, fd);
	write(fd, "\n", 1);
}
