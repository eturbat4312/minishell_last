NAME	= minishell_tory
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g -I/Users/eturbat/.brew/Cellar/readline/8.2.1/include

SRCS	= main.c dup_env.c ft_env.c special_putstr.c\
		  change_env_value.c ft_mtp_strjoin.c my_getenv.c array.c ft_free_tab.c utils_libft.c\
		  ft_isdigit.c ft_isspace.c ft_mtp_putendl_fd.c find_path.c\
			only_redir.c signals.c prepare_heredoc.c prepare_input_out.c prepare_redirections.c validate_redir.c\
			dup_fds.c ft_strchr.c signals_2.c\
			utils/ft_memset.c utils/ft_tab_len.c utils/utils.c \
			error_and_free/error_fct.c error_and_free/free_data.c ft_strfind.c\
			built_ins/ft_cd.c built_ins/ft_pwd.c built_ins/ft_exit.c built_ins/ft_unset.c built_ins/ft_echo_1.c built_ins/ft_echo_2.c\
			built_ins/export/ft_export.c built_ins/export/ft_sort_params.c built_ins/export/print_env.c built_ins/export/utils_export.c\
			execution/exec_cmds.c execution/exec_pipes_2.c execution/exec_pipes_3.c execution/exec_pipes.c execution/find_built_ins.c\
			execution/find_commands.c\
			parse/eval.c parse/locate_char.c parse/parse_process.c parse/parse.c parse/resolve_env.c parse/utils_parse.c parse/parse_redirection.c\
			parse/single_double_quote.c parse/utils_parse_2.c parse/utils_parse_3.c

SRCS_DIR	=	srcs

OBJS		=	$(SRCS:.c=.o)

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

RM	=	rm -f
CLEAN	=	clean

all	:
		make $(NAME)

$(NAME)	:	${OBJS}
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline -L/Users/eturbat/.brew/Cellar/readline/8.2.1/lib

clean	:
		rm -rf ${OBJS}

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all
