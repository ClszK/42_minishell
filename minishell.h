#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h> //readline add_history 등 
# include <stdio.h> //printf  perror
# include <stdlib.h> //malloc free exit getenv 
# include <unistd.h> //write access read close fork getcwd chdir unlink execve dup dup2
					 //pipe isatty ttyname ttyslot 
# include <fcntl.h> //open 
# include <sys/types.h> //pid_t
# include <sys/wait.h> //wait
# include <signal.h> //signal kill sigaction sigemptyset sigaddset 
# include <sys/stat.h> //stat lstat fstat
# include <dirent.h> //opendir readdir closedir
# include <string.h> // strerror 
# include <errno.h> // errno
# include <sys/ioctl.h> //ioctl 
# include <termios.h> //tcsetattr tcgetattr 
# include <curses.h> 
# include <term.h>	//tgetent tgetflag tgetnum tgetstr tgoto tputs

# include "srcs/libft/libft.h"

typedef struct s_parse
{
	/* data */
	char	**cmd_argv;
}	t_parse;

#endif