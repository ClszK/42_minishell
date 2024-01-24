/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:10:11 by ljh               #+#    #+#             */
/*   Updated: 2024/01/24 18:01:40 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_FAILURE 1

# define SYNTAX_ERROR 1

# define READ_FD 0
# define WRITE_FD 1

# define FD_IN 2
# define FD_OUT 3

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

int	g_signo;

enum e_type
{
	NONE,
	WORD,
	PIPE,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
	NEWLN
};

typedef struct s_lst	t_envp;
typedef struct s_lst	t_cmdline;
typedef struct s_lst	t_analyze;
typedef struct s_lst	t_stdio;

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
	t_stdio	*stdin_lst;
	t_stdio	*stdout_lst;
}	t_parse;

typedef struct s_map
{
	char	*key;
	char	*val;
}	t_map;

typedef struct s_shinfo
{
	char		*rline;
	t_envp		env_c;
	t_cmdline	cmdline;
	t_analyze	alz;
}	t_shinfo;

typedef struct s_pinfo
{
	int		pipe_cnt;
	int		pfd[2][2];
	pid_t	pid;
	pid_t	last_pid;
	int		last_status;
}	t_pinfo;

/* utils.c*/
int			ps_move_sign(char *str, int *sign);
long		ft_atol(char *str, int *flag);
enum e_type	operate_type(char *str);
int			is_redirect(t_token *token);
int			is_operator(char ch);

/* utils2.c*/
int			is_dollar_sperator(char ch);
char		check_quote_type(char ch);
int			can_dollar_expand(char *str);
void		arr_one_left_shift(char *str);
char		valid_quote(char *rline);

/* utils3.c*/
int			is_builtin_command(char *cmd);
int			is_include_pipe(t_analyze *alz);
int			is_file_access(char *filename, int mode);

/* set.c */
void		envp_init(char **envp, t_envp *env_c);
void		cmdline_init(t_cmdline *cmdline);
void		analyze_init(t_analyze *alz);
t_stdio		*stdio_init(void);
void		shinfo_init(t_shinfo *sh);

/* print.c */
void		perror_exit(char *progname);
int			print_strerror(char *cmd, char *str);
int			print_builtin_error(char *cmd, char *arg, char *error);
int			print_syntax_error(int type);

/* parse.c */
void		token_cmdline(char *rline, t_cmdline *cmdline);

/* generate.c */
t_token		*token_elem_generate(char *str, enum e_type type);
t_parse		*parse_elem_generate(int cmd_argc);
t_token		*token_elem_cpy(void *elem);

/* analyze.c */
int			analyze_start(t_analyze *alz, t_cmdline *cmdline);
t_node		*analyze_parse_create(t_analyze *alz, t_node *token_node, t_parse *parse);

/* analyze2.c */
int			is_pipe_node(t_node *node);
void		token_redirection_type_change(t_node *node);

/* expand.c */
char		*expand_squote(char *start, size_t *size, char *dst);
char		*expand_dquote(char *start, size_t *size, t_envp *env_c, char *dst);
char		*expand_dollar(char *start, size_t *size, t_envp *env_c, char *dst);
char		*expand_str_alloc(char *start, t_envp *env_c);

/* expand2.c */
char		*expand_str_cpy(char *start, char *dst, t_envp *env_c);
void		expand_cmd_argv(char **cmd_argv, t_envp *env_c);
void		expand_stdio(t_stdio *std, t_envp *env_c);
void		expand_start(t_analyze *alz, t_envp *env_c);

/* path.c */
void		path_insert_in_parse(t_analyze *alz, t_envp *env_c);

/* cmd.c */
void		command_excute(t_analyze *alz, t_envp *env_c);
int			command_excute_builtin(t_parse *parse, t_envp *env_c, int builtin_idx);

/* proc.c */
void		wait_child(t_pinfo *info, int cmd_cnt);
void		child_process(t_parse *parse, t_envp *env_c, int i, t_pinfo *info);

/* file.c */
int			tmpfile_create(char **tmp_name);
int			open_file(char *filename, int mode);
void		stdin_heredoc(char *end_id, int tmp_fd);

/* fd.c */
int 		pipe_init(t_pinfo *pinfo, int cmd_argc);
void		pipe_close(t_pinfo *info, int pos);
int			std_to_fd(t_node *std_node, int i, int std_fd, t_pinfo *info);
void		dup_std_fd(t_pinfo *info, t_stdio *stdin_lst, t_stdio *stdout_lst, int i);

/* builtin */
int			builtin_echo(t_parse *parse);
int			builtin_pwd(t_envp *env_c);
int			builtin_env(t_envp *env_c);
int			builtin_exit(t_parse *parse);
int			builtin_export(t_parse *parse, t_envp *env_c);
int			builtin_unset(t_parse *parse, t_envp *env_c);
int			builtin_cd(t_parse *parse, t_envp *env_c);

/* export2.c*/
void		append_env(char *cmd_argv, t_envp *env_c, size_t equal);
int			check_dup(char	*cmd_argv, t_envp *env_c, size_t equal);
void		update_env(char *cmd_argv, t_map *cur, size_t equal);
void		free_copy(t_map *export_c, long lst_size);
int			export_print_sort(t_map *export_c, int pos);


/* free.c */
void		token_elem_free(void *elem);
void		map_elem_free(void *elem);
void		parse_elem_free(void *elem);
void		split_free(char **arr);
void		shinfo_free(t_shinfo *sh, t_envp *env_c);

/* find.c */
int			map_key_find(void *elem, void *cmp);
void		map_oldpwd_find(t_envp *env_c);
char		*expand_env_find(t_envp *env_c, char *str);
int			find_char(char *str, char c);

/* builtin_utils.c */
int			check_export_key(char *key);
int			check_unset_key(char *key);

/* signal.c */
void		set_signal(void);
void		set_sigterm(void);

/* test in main.c */
void		test_leak(void);

#endif