NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RFLAGS		=	-lreadline

LIB_DIR		=	srcs/libft
LIB			=	-L$(LIB_DIR) -lft

SRCS		=	main.c 	\

OBJS		=	$(SRCS:.c=.o)

HEADER		=	minishell.h

all:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(RFLAGS) $(LIB) $(OBJS) -o $(NAME)

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER)

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
