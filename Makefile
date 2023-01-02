SRCS	=	$(addprefix parse/, parse.c utils.c ) main.c \
			$(addprefix builtins/, pwd.c export.c unset.c exit.c) \
			$(addprefix src/, set_data.c)

NAME	=	minishell

FLAGS	=	-g3  #-Wall -Werror -Wextra -lreadline

OBJS	=	${SRCS:.c=.o}

INC		= -I ./include

all:	${NAME}

${NAME}:	${OBJS}
		make -C ./libft/
		cc ${FLAGS} ${INC} ${OBJS} -o ${NAME} ./libft/libft.a -lreadline

%.o:%.c
	cc ${FLAGS} -c $< -o $@

clean:
	make -C ./libft/ clean
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re:	fclean all

.PHONY:	all clean fclean re