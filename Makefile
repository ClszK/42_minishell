NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RFLAGS		=	-lreadline
LIB			=	-Llibft -lft

SRCS		=	main.c 	\

OBJS		=	$(SRCS:.c=.o)

HEADER		=	minishell.h

all:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
	make -C ./libft/
	$(CC) $(CFLAGS) $(RFLAGS) $(LIB) $(OBJS) -o $(NAME)

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER)

clean:
	rm -rf $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: 
	make fclean
	make all

.PHONY : all clean fclean re 
