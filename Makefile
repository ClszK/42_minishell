NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra
RFLAGS			=	-lreadline

LIB_DIR			=	srcs/lib/libft
LIB				=	-L$(LIB_DIR) -lft

SRCS_J			=	main_j.c

SRCS_S			=	main_s.c

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
					cmd.c

SRCS_BUILTIN	=	echo.c\
					pwd.c\
					env.c\
					exit.c\
					export.c\
					unset.c\
					cd.c

SRCS_DOUBLE		=	double_lst.c\
					double_lst2.c

OBJS			=	$(addprefix srcs/utils/, ${SRCS_UTILS:.c=.o})\
					$(addprefix builtin/, ${SRCS_BUILTIN:.c=.o})\
					$(addprefix srcs/lib/double/, ${SRCS_DOUBLE:.c=.o})

HEADERS			=	double_lst.h\
					minishell.h

HEADERS_PATH	=	includes

ifdef MY
    OBJ = $(OBJS) $(SRCS_J:.c=.o)
else
    OBJ = $(OBJS) $(SRCS_S:.c=.o)
endif

all:	$(NAME)

$(NAME)	:	$(OBJ) $(addprefix includes/, ${HEADERS})
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(RFLAGS) $(LIB) $(OBJ) -o $(NAME) -fsanitize=address

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADERS_PATH) -g

clean:
	rm -rf $(OBJ)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re: 
	make fclean
	make all

.PHONY : all clean fclean re 
