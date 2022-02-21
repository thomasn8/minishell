SRCS	= 	ft_atoi.c				\
			ft_isalnum.c			\
			ft_itoa_base16.c		\
			ft_itoa.c				\
			ft_memmove.c			\
			ft_putendl.c			\
			ft_split.c				\
			ft_striteri.c			\
			ft_strlen.c				\
			ft_strtrim.c			\
			ft_bzero.c				\
			ft_isalpha.c			\
			ft_itoa.c				\
			ft_memset.c				\
			ft_putnbr_fd.c			\
			ft_split_quotes.c		\
			ft_strjoin_3.c			\
			ft_strmapi.c			\
			ft_substr.c				\
			ft_calloc.c				\
			ft_isascii.c			\
			ft_memchr.c				\
			ft_notblank.c			\
			ft_putstr_fd.c			\
			ft_strchr_bn.c			\
			ft_strjoin.c			\
			ft_strncmp.c			\
			ft_tolower.c			\
			ft_cut_strnstr.c		\
			ft_isdigit.c			\
			ft_memcmp.c				\
			ft_print_args.c			\
			ft_printf.c				\
			ft_replace_strnstr.c	\
			ft_strchr.c				\
			ft_strlcat.c			\
			ft_strnstr.c			\
			ft_toupper.c			\
			ft_free_array.c			\
			ft_isprint.c			\
			ft_memcpy.c				\
			ft_putchar_fd.c			\
			ft_split_blank.c		\
			ft_strdup.c				\
			ft_strlcpy.c			\
			ft_strrchr.c			\
			get_next_line.c			\

OBJS	= ${SRCS:.c=.o}
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a
RM		= rm -f

############################## rules

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib $(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

.PHONY:		all clean fclean re

re:			fclean all
