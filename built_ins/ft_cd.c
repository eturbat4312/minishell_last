/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:56:07 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/30 12:59:38 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!strncmp(env[i], "HOME=", 5))
			return (env[i] + 5);
	return (NULL);
}

int	old_pwd(char **env, t_mini *mini)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			if (chdir(env[i] + 7) == -1)
				ft_putendl_fd("minishell: cd: OLD PWD error\n", STDERR_FILENO);
			tmp = getcwd(NULL, 0);
			replace_pwd(mini, env[i] + 7, 0);
			printf("%s\n", env[i] + 7);
			free(mini->env[i]);
			mini->env[i] = ft_strjoin(ft_strdup("OLDPWD="), tmp);
			free(tmp);
			return (1);
		}
	}
	ft_putendl_fd("minishell: cd: OLD PWD error\n", STDERR_FILENO);
	return (0);
}

int	check_args(char **complete_cmd, t_mini *mini)
{
	if (complete_cmd[1] == NULL || !ft_strncmp(complete_cmd[1], "~\0", 2))
	{
		if (get_home(mini->env) == NULL)
			ft_putendl_fd("minishell: cd: HOME error\n", STDERR_FILENO);
		chdir(get_home(mini->env));
		return (0);
	}
	else if (!ft_strncmp(complete_cmd[1], "-\0", 2))
		return (old_pwd(mini->env, mini));
	if (complete_cmd[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return (-1);
	}
	else if (chdir(complete_cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(complete_cmd[1]);
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

void	ft_cd(char **complete_cmd, t_mini *mini)
{
	char	*pwd;

	if (check_args(complete_cmd, mini) == -1)
		return ;
	change_env_value(mini, "OLDPWD", my_getenv("PWD", mini->env));
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		change_env_value(mini, "PWD", pwd);
		free(pwd);
	}
	g_exit_status = 0;
}
