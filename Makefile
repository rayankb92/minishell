SRCS = $(addprefix parse/, parse.c) main.c


NAME = minishell


INC = -I ./include

FLAGS = -g3 -Wall -Werror -Wextra 

OBJS = ${SRCS:.c=.o}

LIBFT = libft/libft.a

${NAME} : ${OBJS} ${LIBFT}
			make -C libft/ all
			gcc ${FLAGS} ${INC} $(OBJS) -o $(NAME) libft/libft.a -lreadline

${LIBFT}:
	make -C libft/ all

all : ${NAME}

%.o:%.c
		gcc ${FLAGS} -c $< -o $@

bonus: ${NAME_BONUS}


clean :
		make -C ./libft/ clean
		rm -rf ${OBJS} 
fclean : clean
		rm -rf ${NAME} ${NAME_BONUS}
		make -C ./libft/ fclean

re : fclean all

.PHONY : all bonus clean fclean re bonus INC libft NAME NAME_BONUS