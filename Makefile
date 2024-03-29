NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
R_FLAGS			=	-lreadline -L${HOME}/.brew/opt/readline/lib
ROBJ_FLAGS		=	-I${HOME}/.brew/opt/readline/include

LIB_DIR			=	lib/libft
LIB				=	-L$(LIB_DIR) -lft

SRCS			=	main.c

SRCS_PARSER		=	analyze.c\
					analyze2.c\
					parse.c\
					expand.c\
					expand2.c\
					path.c\
					path2.c

SRCS_EXEC		=	fd.c\
					fd2.c\
					proc.c\
					pipe.c\
					cmd.c

SRCS_UTILS		=	utils.c\
					utils2.c\
					utils3.c\
					set.c\
					set2.c\
					print.c\
					generate.c\
					free.c\
					signal.c\
					signal2.c\
					find.c\
					file.c

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
					$(addprefix srcs/parser/, ${SRCS_PARSER:.c=.o})\
					$(addprefix srcs/exec/, ${SRCS_EXEC:.c=.o})\
					$(addprefix srcs/builtin/, ${SRCS_BUILTIN:.c=.o})\
					$(addprefix lib/double/, ${SRCS_DOUBLE:.c=.o})

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
