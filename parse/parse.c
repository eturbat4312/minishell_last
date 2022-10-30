/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srituit <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:17:31 by srituit           #+#    #+#             */
/*   Updated: 2022/10/30 16:18:44 by srituit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_process(t_mini *data, int i)
{
	size_t	j;

	if (data->process[i].params)
	{
		ft_free_tab(data->process[i].params);
		data->process[i].params = NULL;
	}
	j = 0;
	while (j < data->process[i].redirs.lenght / 2)
	{
		free(data->process[i].redirs.elements[j * 2 + 1]);
		data->process[i].redirs.elements[j * 2 + 1] = NULL;
		j++;
	}
	delete_array(&data->process[i].redirs);
	if (data->process[i].fd_input > -1)
	{
		close(data->process[i].fd_input);
		data->process[i].fd_input = -1;
	}
	if (data->process[i].fd_output > -1)
	{
		close(data->process[i].fd_output);
		data->process[i].fd_output = -1;
	}
}

void	init_process(t_process *process)
{
	process->params = NULL;
	process->redirs = new_array();
	process->fd_input = -1;
	process->fd_output = -1;
	process->error = false;
}

int	prepare_parse(char **tmp, t_mini *mini)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (only_redir(tmp[i]))
		{
			error_fct3("syntax error near unexpected token 1 ", "newline\n", 2);
			return (free_data_s(tmp, mini));
		}
		if (!(parse_process(tmp[i], &mini->process[i], mini)))
			return (free_data_s(tmp, mini));
		if (!(validate_redir(&mini->process[i])))
		{
			error_fct3("syntax error near unexpected token ", "< or >'\n", 2);
			return (free_data_s(tmp, mini));
		}
		if (!mini->process[i].params)
			error_fct(mini, "Minishell: Malloc Failure!!!", 2);
		i++;
	}
	return (1);
}

t_process	*from_line_to_process(t_mini *mini)
{
	int		i;
	char	**tmp;

	if (all_space(mini->line))
		return (0);
	tmp = split(mini->line, '|');
	if (!check_all_space(tmp))
		return (0);
	mini->nb_processes = count_elements((void **)tmp);
	mini->process = malloc(mini->nb_processes * sizeof(t_process));
	if (!mini->process)
		error_fct(mini, "minishell: Malloc failure", 2);
	i = 0;
	while (i < mini->nb_processes)
	{
		init_process(&mini->process[i]);
		i++;
	}
	if (!prepare_parse(tmp, mini))
		return (0);
	ft_free_tab(tmp);
	return (mini->process);
}

void	parse(t_mini *mini)
{
	mini->process = from_line_to_process(mini);
	if (!mini->process)
		return ;
	prepare_redirections(mini);
	remove_faulty_processes(mini);
	if (mini->nb_processes == 1)
	{
		exec_cmds(mini);
	}
	else if (mini->nb_processes > 1)
		exec_pipes(mini, mini->nb_processes - 1);
	free_processes(mini);
}
