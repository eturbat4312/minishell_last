/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:19:04 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 13:22:56 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **my_envp)
{
	char	*pathname;
	char	*env_pwd;

	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		env_pwd = my_getenv("PWD", my_envp);
		if (!env_pwd)
		{
			ft_putstr_fd("minishell: pwd: information not available\n",
				STDERR_FILENO);
			g_exit_status = 1;
			return ;
		}
		pathname = ft_strdup(env_pwd);
	}
	if (!special_putend(pathname, STDOUT_FILENO))
	{
		perror("minishell: pwd: write error");
		g_exit_status = 1;
		free(pathname);
		return ;
	}
	free(pathname);
	g_exit_status = 0;
}

int	get_pwd_pos(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (i);
	return (-1);
}

void	replace_pwd(t_mini *sh, char *dir, int code)
{
	int		pos;

	pos = get_pwd_pos(sh->env);
	free(sh->env[pos]);
	sh->env[pos] = ft_strjoin(ft_strdup("PWD="), dir);
	if (!dir)
		free(dir);
	if (code == 1)
		free(dir);
}
