NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra
R_FLAGS			=	-lreadline -L/opt/homebrew/opt/readline/lib #-L${HOME}/.brew/opt/readline/lib
ROBJ_FLAGS		=	-I/opt/homebrew/opt/readline/include #-I${HOME}/.brew/opt/readline/include

LIB_DIR			=	srcs/lib/libft
LIB				=	-L$(LIB_DIR) -lft

SRCS			=	main.c

SRCS_UTILS		=	utils.c\
					utils2.c\
					utils3.c\
					set.c\
					print.c\
					parse.c\
					generate.c\
					analyze.c\
					analyze2.c\
					free.c\
					find.c\
					expand.c\
					expand2.c\
					path.c\
					cmd.c\
					proc.c\
					fd.c\
					file.c\
					signal.c

SRCS_BUILTIN	=	echo.c\
					pwd.c\
					env.c\
					exit.c\
					export.c\
					export2.c\
					unset.c\
					cd.c

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
	$(CC) $(CFLAGS) $(R_FLAGS) $(LIB) $(OBJS) -o $(NAME)

%.o	:	%.c
	$(CC) $(CFLAGS) $(ROBJ_FLAGS) -c $< -o $@ -I$(HEADERS_PATH) -g

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
