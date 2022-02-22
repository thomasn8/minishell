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


OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= minishell
RM			= rm -f

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L./libft -lft

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make --silent -C ${LIBFT_DIR}/
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS} $(LIBFT) -lreadline

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

#-------HELP TO DEBUG---------#

#-g -fsanitize=address ou -O0 à ajouter lors de la compliation pour le débegueur vscode.
#leaks -atExit -- ./commande (mac) qui permet de checker si il y'a des leaks.
#valgrind --leak-check=full --show-leak-kinds=all ./minishell
