/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtp_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:24:01 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 15:24:15 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_mtp_strjoin(char *s1, char *s2, char *s3)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
	{
		perror("ft_mtp_strjoin: Malloc error");
		exit(3);
	}
	new = ft_strjoin(tmp, s3);
	free(tmp);
	if (!new)
	{
		perror("ft_mtp_strjoin: Malloc error");
		exit(3);
	}
	return (new);
}
