/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:08:30 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:15:15 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_digits(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			count++;
		i++;
	}
	return (count);
}

int	check_nb(char *str, long long *nb)
{
	int			i;
	int			neg;
	long long	nbr;

	i = 0;
	nbr = 0;
	neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		nbr = (nbr * 10) + str[i++] - 48;
		if (nbr < 0)
			return (0);
	}
	*nb = nbr * neg;
	return (1);
}

void	exit_nb(t_mini *mini, long long nb)
{
	g_exit_status = nb;
	free_data(mini);
	exit(g_exit_status);
}

void	ft_exit(char **complete_cmd, t_mini *data)
{
	long long	nb;

	nb = 0;
	if (complete_cmd[1])
	{
		if (complete_cmd[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			g_exit_status = 1;
			return ;
		}
		if (!has_digits(complete_cmd[1]) || !check_nb(complete_cmd[1], &nb))
		{
			ft_mtp_putendl_fd(STDERR_FILENO, "minishell: exit: ",
				complete_cmd[1], ": numeric argument required");
			g_exit_status = 2;
			free_data(data);
			exit(g_exit_status);
		}
		else
		{
			exit_nb(data, nb);
		}
	}
	exit_nb(data, g_exit_status);
}
