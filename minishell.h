/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturbat <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:03:41 by eturbat           #+#    #+#             */
/*   Updated: 2022/10/29 16:14:14 by eturbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

# define NF ": command not found"
# define ISD ": Is a directory"
# define MAX_ALLOC 1000
# define ERR_OPE "Operation error!\n"

int	g_exit_status;

typedef struct s_array
{
	size_t	lenght;
	size_t	capacity;
	void	**elements;
}	t_array;

typedef struct s_process
{
	char	**params;
	int		fd_input;
	int		fd_output;
	bool	error;
	t_array	redirs;
}	t_process;

typedef struct s_elements
{
	int		*child;
	int		*built_in;
	int		**pipe_fd;
}			t_elements;

typedef struct s_mini
{
	char				**separated_line;
	char				*line;
	char				**path;
	char				*arg;
	char				*token;
	char				*command;
	char				*message;
	char				*file;
	char				**env;
	t_process			*process;
	int					nb_processes;
	struct sigaction	sigint;
	struct sigaction	sigquit;
}	t_mini;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
void	do_cd(t_mini *mini);
void	do_pwd(t_mini *mini);
void	do_echo(t_mini *mini);
void	do_exit(t_mini *mini);
void	do_env(t_mini *mini);
size_t	ft_strlen(const char *s);
int		special_putend(char *s, int fd);
char	**dup_env(char *envp[]);
int		ft_tab_len(char **tab);
void	*ft_memset(void *b, int c, size_t len);
void	parse(t_mini *mini);
void	exec_pipes(t_mini *mini, int nb_pipes);
void	free_processes(t_mini *mini);
void	do_command(t_mini *mini);
int		get_command_and_arg(char **separated_line, t_mini *mini);
t_array	new_array(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	exec_cmds(t_mini *mini);
void	dup_fds(t_mini *mini, int *stdin_copy, int *stdout_copy);
int		find_built_ins(char *cmd);
void	ft_cd(char **complete_cmd, t_mini *mini);
void	error_fct(t_mini *mini, char *msg, int exit_value);
void	*my_malloc(size_t size);
void	error_fct2(char *msg, int exit_value);
void	error_fct3(char *msg, char *err_str, int exit_value);
void	change_env_value(t_mini *mini, char *var, char *new_value);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_data(t_mini *mini);
char	*my_getenv(char *name, char **my_envp);
char	*ft_mtp_strjoin(char *s1, char *s2, char *s3);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
bool	parse_process(char *s, t_process *process, t_mini *mini);
void	*new_memory(size_t size);
int		locate_chars(char *s, char *delimiters);
int		trim(char *s);
char	*resolve_env(char *s, t_mini *data);
int		skip_spaces(char *str, int i);
char	*ft_substr(const char *s, unsigned int start_pos, size_t len);
void	copy_then_free(char *src, int *i, char *dst);
void	ft_free_tab(char **tab);
void	delete_array(t_array *arr);
void	free_process(t_mini *data, int i);
char	*eval(char *s, t_mini *mini);
char	*ft_strdup(const char *str);
char	*ft_itoa(int nbr);
char	*active_env(char *s);
int		find_pos(const char *haystack, const char *needle, int len);
char	*strjoin(char const *s1, char const *s2);
char	*deactive_env(char *s);
int		find_built_ins(char *cmd);
void	ft_pwd(char **my_envp);
void	ft_env(char **complete_cmd, char **env);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_mtp_putendl_fd(int fd, char *s1, char *s2, char *s3);
void	ft_exit(char **complete_cmd, t_mini *data);
void	remove_env(char *var, t_mini *data);
int		check_env(char *s);
void	add_env(char *var, t_mini *data, int pos_equal);
void	ft_unset(char **cmd, t_mini *data);
int		count_elements(void **arr);
int		check_env_ex(char *s);
int		special_putstr(char *s, int fd);
int		special_putchar(char c, int fd);
void	ft_sort_params(char **tab, int size);
void	sort_print(t_mini *data);
void	ft_export(char **cmd, t_mini *mini);
char	**find_path(char **env);
int		special_mtp_putstr(char *s1, char *s2, char *s3, int fd);
int		check_cases(char **complete_cmd, int i, int newline, int save_index);
void	ft_echo(char **complete_cmd);
int		ft_strfind(char c, char *s);
bool	all_space(char *s);
bool	only_redir(char *s);
int		validate_redir(t_process *process);
void	prepare_redirections(t_mini *data);
int		prepare_redirs(t_mini *data, int process_id);
int		prepare_heredoc(t_mini *data, char *filename, char *end, bool do_eval);
void	main_sigint_handler(int signum);
void	end_heredoc(char *end);
void	close_redirection_fds(t_mini *data);
bool	is_char_in(char ch, char *delimiters);
int		parse_redirection(char *s, int i, t_process *process, t_mini *data);
void	array_append(t_array *arr, void *new_element);
char	*ft_strchr(const char *s, int c);
void	child_sigquit_handler(int signum);
char	**find_cmds(char **complete_cmd, t_mini *data);
void	check_all_cmds(t_mini *mini, t_elements *elements, int nb_pipes);
void	first_process(t_mini *mini, t_elements *elements, int i);
void	last_process(t_mini *mini, t_elements *elements, int i);
void	free_elements(t_elements *elements, int nb_pipes);
void	middle_process(t_mini *data, t_elements *elements, int i);
void	replace_pwd(t_mini *sh, char *dir, int code);
void	init_signals(t_mini *data);
void	signal_handler(int sig);
void	ft_signals(struct termios *save);
void	remove_faulty_processes(t_mini *data);
void	init_process(t_process *process);
char	**split(char *s, char delimiter);
int		locate_char(char *s, char delimiter);
void	malloc_elements(t_mini *mini, t_elements *elements, int nb_pipes);
void	close_fds(t_mini *mini, int **pipe_fd, int index);
char	*scan_double_quoted(char *s, int *i);
char	*scan_single_quoted(char *s, int *i);
char	*scan_unquoted(char *s, int *i);
char	*new_string(int capacity);
int		free_data_s(char **tmp, t_mini *data);
int		count_elements(void **arr);
int		check_all_space(char **tmp);
void	free_processes(t_mini *mini);
int		ft_countword(char const *s1, char del);
char	*ft_putstr(char const *str, size_t start, size_t end);

#endif
