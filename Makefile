SRCS	=	$(addprefix parse/, parse.c utils.c) main.c \
			$(addprefix builtins/, pwd.c cd.c export.c unset.c)

NAME	=	minishell

FLAGS	=	-g3 -lreadline #-Wall -Werror -Wextra -lreadline

OBJS	=	${SRCS:.c=.o}

INC		= -I ./include

all:	${NAME}

${NAME}:	${OBJS}
		make -C ./libft/ fclean
		make -C ./libft/ any
		cc ${FLAGS} ${INC} ${OBJS} -o ${NAME} ./libft/libft.a

%.o:%.c
	cc ${FLAGS} -c $< -o $@

clean:
	make -C ./libft/ clean
	rm -rf ${OBJS}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re