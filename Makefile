SRCS		= 	srcs/main.c 					\
				srcs/config.c					\
				srcs/prompt.c					\
				srcs/signals.c					\
				srcs/free_datas.c				\
				srcs/parse/parse.c				\
				srcs/parse/parse_syntax.c		\
				srcs/parse/parse_lists.c		\
				srcs/parse/parse_redir1.c		\
				srcs/parse/parse_redir2.c		\
				srcs/parse/parse_args.c			\
				srcs/parse/parse_utils.c		\
				srcs/parse/parse_expansion.c	\
				srcs/parse/parse_expansion2.c	\
				srcs/parse/print_lists.c		\
				srcs/builtins/builtins.c		\
				srcs/builtins/pwd.c				\
				srcs/builtins/cd.c				\
				srcs/builtins/cd_utils.c		\
				srcs/builtins/echo.c			\
				srcs/builtins/exit.c			\
				srcs/builtins/export.c			\
				srcs/builtins/export2.c			\
				srcs/builtins/unset.c			\
				srcs/builtins/env.c				\
				srcs/execution/execution1.c		\
				srcs/execution/execution2.c		\
				srcs/execution/redir_inputs.c	\
				srcs/execution/redir_outputs.c	\

# in order to use all readline functions, you may want to "brew install readline"
# link the new CFLAGS path
# link the readline path to your installed library in the READLINE variable

OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I/usr/local/opt/readline/include
NAME		= minishell
RM			= rm -f
LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L./libft -lft
READLINE	= -L/usr/local/opt/readline/lib

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make --silent -C ${LIBFT_DIR}/
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS} $(LIBFT) -lreadline $(READLINE)

clean:
			${RM} ${OBJS}
			make --silent -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}
			make --silent -C ${LIBFT_DIR} fclean

re:			fclean all

run:		
			./${NAME}

.PHONY:		all clean fclean re run


###### Debuging
# -g -fsanitize=address
# valgrind --leak-check=full --show-leak-kinds=all ./minishell
# -O0 pour le débegueur vscode.
