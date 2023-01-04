# SRCS	=	$(addprefix parse/, parse.c utils.c ) main.c \
# 			$(addprefix builtins/, pwd.c export.c unset.c exit.c) \
# 			$(addprefix src/, set_data.c)

# NAME	=	minishell

# FLAGS	=	-g3  #-Wall -Werror -Wextra -lreadline

# OBJS	=	${SRCS:.c=.o}

# DEPS		=	${OBJS:.o=.d}

# INC		= -I ./include

# all:	${NAME}

# ${NAME}:	${OBJS}
# 		make -C ./libft/
# 		cc ${FLAGS} ${INC} ${OBJS} -o ${NAME} ./libft/libft.a -lreadline

# -include: ${DEPS}

# %.o:%.c
# 	cc ${FLAGS} -c -MMD -MP $< -o $@

# clean:
# 	make -C ./libft/ clean
# 	rm -rf ${OBJS}

# fclean:	clean
# 	rm -rf ${NAME}

# re:	fclean all

# .PHONY:	all clean fclean re


 #=============================================================================#
#								SOURCES											#
 #=============================================================================#

SRCS_DIR = src
BLTS_DIR = builtins
PRSG_DIR = parse
SIGNAL_DIR = signal
INTERPRET_DIR = interpret_input
SRCS_DIRS = $(SRCS_DIR)\
			$(BLTS_DIR)\
			$(PRSG_DIR)\
			$(SIGNAL_DIR)\
			$(INTERPRET_DIR)\

SRC_FILES =	$(addprefix parse/, parse.c utils.c ) main.c \
			$(addprefix builtins/, pwd.c export.c unset.c exit.c) \
			$(addprefix signal/, ctrlc.c) \
			$(addprefix interpret_input/, interpret_input.c is_exit.c) \
			$(addprefix src/, set_data.c)
				

#SRCS = $(addsuffix .c, $(SRC_FILES))

 #=============================================================================#
#									OBJETS										#
 #=============================================================================#

OBJS_DIR = objets
OBJS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.d)

 #=============================================================================#
#									LIBRARY										#
 #=============================================================================#

LIB_DIR = libft

 #=============================================================================#
#									COMPILATION									#
 #=============================================================================#

CC = gcc
CFLAGS = -g3# -Wall -Wextra -Werror -lreadline
CDFLAGS = -MMD -MP
CIFLAGS = -Iincludes -I$(LIB_DIR)/includes
CLFLAGS = -L$(LIB_DIR) -lft -lreadline

 #=============================================================================#
#									MAKEFILE									#
 #=============================================================================#

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CLFLAGS) -o $(NAME)

$(OBJS_DIR) :
	$(MAKE) -C $(LIB_DIR)
	mkdir $(OBJS_DIR)
	mkdir $(OBJS_DIR)/$(SRCS_DIR)
	mkdir $(OBJS_DIR)/$(BLTS_DIR)
	mkdir $(OBJS_DIR)/$(PRSG_DIR)
	mkdir $(OBJS_DIR)/$(SIGNAL_DIR)
	mkdir $(OBJS_DIR)/$(INTERPRET_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re

#.SILENT:
