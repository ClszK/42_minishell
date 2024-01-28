/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:10:11 by ljh               #+#    #+#             */
/*   Updated: 2024/01/28 23:09:47 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_FAILURE 1

# define SYNTAX_ERROR 1
# define SQUOTE_ERROR 8
# define DQUOTE_ERROR 9

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>

# include "double_lst.h"

int						g_signo;

typedef struct s_lst	t_envp;
typedef struct s_lst	t_cmdline;
typedef struct s_lst	t_analyze;
typedef struct s_lst	t_stdio;

enum e_type
{
	NONE,
	WORD,
	PIPE,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
	NEWLN,
	PIPE_IN,
	PIPE_OUT
};

typedef struct s_token
{
	enum e_type	type;
	char		*str;
	char		*env_val;
}	t_token;

typedef struct s_parse
{
	int		cmd_argc;
	char	*cmd_path;
	char	**cmd_argv;
	t_stdio	*std_lst;
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
	t_stdio		heredoc;
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
int			check_quote_type(char ch);
int			can_dollar_expand(char *str);
void		arr_one_left_shift(char *str);
int			valid_quote(char *rline);

/* utils3.c*/
int			is_builtin_command(char *cmd);
int			is_include_pipe(t_analyze *alz);
int			is_file_access(char *filename, int mode);
void		split_shift(char **str, int i);
char		*str_push_space(char *str);

/* set.c */
void		cmdline_init(t_cmdline *cmdline);
void		analyze_init(t_analyze *alz);
t_stdio		*stdio_init(void);
void		shinfo_init(t_shinfo *sh);

/* set2.c */
void		envp_init(char **envp, t_envp *env_c);
void		set_env_pwd(t_envp *env_c);

/* print.c */
void		perror_exit(char *progname);
int			print_strerror(char *cmd, char *str);
int			print_builtin_error(char *cmd, char *arg, char *error);
int			print_syntax_error(int type);
void		print_cmd_path_error(char *cmd, t_envp *env_c);

/* parse.c */
void		token_cmdline(char *rline, t_cmdline *cmdline);

/* generate.c */
t_token		*token_elem_generate(char *str, enum e_type type);
t_parse		*parse_elem_generate(int cmd_argc);
t_token		*token_elem_cpy(void *elem, enum e_type type);

/* analyze.c */
int			analyze_start(t_analyze *alz, t_cmdline *cmdline, t_stdio *heredoc);
t_node		*analyze_parse_create(t_analyze *alz, t_node *token_node, \
											t_parse *parse, t_stdio *heredoc);
int			analyze_token_parse(t_node *token_node, t_parse *parse, \
											int *i, t_stdio *heredoc);

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
char		**path_find_in_env(t_envp *env_c);
char		*path_cmd(char *path, char *cmd);
char		*path_cmd_valid(char **path, char *cmd);
char		*cmd_path_in_slash(char *cmd, t_envp *env_c);
int			path_in_dot_dot_check(char *cmd, t_envp *env_c);

/* path2.c */
char		*path_cmd_path(char *cmd, t_envp *env_c);
void		path_insert_in_parse(t_analyze *alz, t_envp *env_c);

/* cmd.c */
void		command_excute(t_analyze *alz, t_envp *env_c, t_stdio *heredoc);
int			command_excute_builtin(t_parse *parse, t_envp *env_c, \
											int builtin_idx, int is_fork);
int			command_preprocessing(t_shinfo *sh);

/* proc.c */
void		wait_child(t_pinfo *info, t_envp *env_c, int cmd_cnt);
void		child_process(t_parse *parse, t_envp *env_c, int i, t_pinfo *info);

/* file.c */
int			tmpfile_create(char **tmp_name);
int			open_file(char *filename, int mode);
int			open_append(char *filename, int fd);
void		delete_heredoc(void);

/* fd.c */
int			dup2_to_std(int fd, t_token *token);
int			open_redirection(t_token *token, int fd);
int			std_to_fd(t_node *std_node);
void		dup_std_fd(t_pinfo *info, t_parse *parse, int i);

/* fd2.c */
int			simple_fd_open(int *fd, t_parse *parse);
int			simple_fd_close(int *fd);
void		child_heredoc_process(char *eof, int tmp_fd);
int			heredoc_process(t_node *heredoc_node, t_envp *env_c, \
											int status, int tmp_fd);

/* builtin */
int			builtin_echo(t_parse *parse);
int			builtin_pwd(t_envp *env_c);
int			builtin_env(t_envp *env_c);
int			builtin_exit(t_parse *parse, int is_fork);
int			builtin_export(t_parse *parse, t_envp *env_c);
int			builtin_unset(t_parse *parse, t_envp *env_c);
int			builtin_cd(t_parse *parse, t_envp *env_c);

/* export2.c*/
void		append_env(char *cmd_argv, t_envp *env_c, size_t equal);
int			check_dup(char	*cmd_argv, t_node *env_node, size_t equal);
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
void		map_oldpwd_find(t_envp *env_c, t_node *env_node);
char		*expand_env_find(t_envp *env_c, char *str);
int			find_char(char *str, char c);

/* pipe.c */
int			pipe_init(t_pinfo *pinfo, int cmd_argc);
void		pipe_close(t_pinfo *info, int pos);
void		pipe_parrent_init(t_pinfo *info, int pos);
void		pipe_std_dup(t_stdio *std, t_pinfo *info, int pos);

/* signal.c */
void		set_signal(void);
void		set_sigterm(void);
void		set_terminal(int flag);
void		restore_signal(void);
void		sigint_handler(int signo);

void		set_signal_child(void);
void		is_fork_signal(int status, int last_status);
void		heredoc_handler(int signo);
void		heredoc_signal(void);

#endif