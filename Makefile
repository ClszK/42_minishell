NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra
RFLAGS			=	-lreadline

LIB_DIR			=	srcs/lib/libft
LIB				=	-L$(LIB_DIR) -lft

SRCS			=	main.c 	\

SRCS_UTILS		=	set.c\
					print.c

SRCS_BUILTIN	=	echo.c\
					pwd.c\
					env.c

SRCS_DOUBLE		=	double_lst.c\
					double_lst2.c

OBJS			=	$(SRCS:.c=.o)\
					$(addprefix srcs/utils/, ${SRCS_UTILS:.c=.o})\
					$(addprefix builtin/, ${SRCS_BUILTIN:.c=.o})\
					$(addprefix srcs/lib/double/, ${SRCS_DOUBLE:.c=.o})

HEADERS			=	double_lst.h\
					minishell.h

HEADERS_PATH	=	includes

all:	$(NAME)

$(NAME)	:	$(OBJS) $(addprefix includes/, ${HEADERS})
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(RFLAGS) $(LIB) $(OBJS) -o $(NAME) 

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADERS_PATH)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re: 
	make fclean
	make all

.PHONY : all clean fclean re 
