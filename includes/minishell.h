/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:10:11 by ljh               #+#    #+#             */
/*   Updated: 2024/01/17 13:18:12 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_FAILURE 1

# define SYNTAX_ERROR 1

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>		// readline add_history 등 
# include <stdio.h> 				// printf  perror
# include <stdlib.h> 				// malloc free exit getenv 
# include <unistd.h> 				// write access read close fork getcwd 
									// chdir unlink execve dup dup2
									// pipe isatty ttyname ttyslot
# include <fcntl.h>					// open 
# include <sys/types.h>				// pid_t
# include <sys/wait.h>				// wait
# include <signal.h>				// signal kill sigaction sigemptyset 
									// sigaddset 
# include <sys/stat.h>				// stat lstat fstat
# include <dirent.h>				// opendir readdir closedir
# include <string.h>				// strerror 
# include <errno.h>					// errno
# include <sys/ioctl.h>				// ioctl 
# include <termios.h>				// tcsetattr tcgetattr 
# include <curses.h>
# include <term.h>					// tgetent tgetflag tgetnum tgetstr
									// tgoto tputs

# include "double_lst.h"

enum e_type
{
	NONE,
	WORD,
	PIPE,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC
};

typedef struct s_token
{
	enum e_type	type;
	char		*str;
}	t_token;

typedef struct s_parse
{
	int		cmd_argc;
	char	*cmd_path;
	char	**cmd_argv;
	t_token	*stdin_token;
	t_token	*stdout_token;
}	t_parse;

typedef struct s_map
{
	char	*key;
	char	*val;
}	t_map;

typedef struct s_lst	t_envp;
typedef struct s_lst	t_cmdline;
typedef struct s_lst	t_analyze;

/* utils.c*/
long		ft_atol(char *str, int *flag);
enum e_type	token_type(char *str);

/* set.c */
void		envp_init(char **envp, t_envp *env_c);
void		cmdline_init(t_cmdline *cmdline);
void		analyze_init(t_analyze *alz);

/* print.c */
void		perror_exit(char *progname);

/* parse.c */
void		token_cmdline(char *rline, t_cmdline *cmdline);

/* generate.c */
t_token		*token_elem_generate(char *str);
t_parse		*parse_elem_generate(int cmd_argc);

/* analyze.c*/
int			analyze_start(t_analyze *alz, t_cmdline *cmdline);
t_node		*analyze_parse_create(t_analyze *alz, t_node *token_node, int cmd_argc);

/* builtin */
int			builtin_echo(t_parse *parse);
int			builtin_pwd(void);
int			builtin_env(t_envp *env_c);
int			builtin_exit(t_parse *parse);
int			builtin_export(t_parse *parse, t_envp *env_c);
int			builtin_unset(t_parse *parse, t_envp *env_c);

/* free.c */

void		token_elem_free(void *elem);
void		map_elem_free(void *elem);
void		parse_elem_free(void *elem);

/* find.c */
int			map_del_find(void *elem, void *cmp);

/* builtin_utils.c */
int			check_key(char *key);


#endif