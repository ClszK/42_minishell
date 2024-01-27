/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:31:07 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 19:37:42 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	환경변수 안에 있는 PATH를 찾아서 ft_split으로 분리한 값 반환.
*/
char	**path_find_in_env(t_envp *env_c)
{
	char	**path;
	char	*path_line;

	errno = 0;
	path_line = expand_env_find(env_c, "PATH");
	if (path_line)
	{
		path = ft_split(path_line, ':');
		if (path == NULL && errno != 0)
			exit(errno);
		return (path);
	}
	return (NULL);
}

/*
	분리된 PATH값을 명령어랑 붙이는 작업.
	ls가 들어오면
	/bin ls를 join으로 합침.
	/bin/ls
*/
char	*path_cmd(char *path, char *cmd)
{
	char	*rcmd;
	char	*tmp;

	errno = 0;
	rcmd = ft_strjoin(path, "/");
	if (rcmd == NULL && errno != 0)
		exit(errno);
	tmp = rcmd;
	rcmd = ft_strjoin(rcmd, cmd);
	free(tmp);
	if (rcmd == NULL && errno != 0)
		exit(errno);
	return (rcmd);
}

/*
	join 시킨 명령어가 존재하는지 체크하고 존재하면 해당 명령어 반환하는 함수.
*/
char	*path_cmd_valid(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = -1;
	if (path == NULL)
		return (NULL);
	while (path[++i] && *cmd)
	{
		errno = 0;
		cmd_path = path_cmd(path[i], cmd);
		if ((access(cmd_path, X_OK) == 0))
			return (cmd_path);
		free(cmd_path);
		if (errno == EACCES)
			break ;
	}
	return (NULL);
}

/*
	경로가 들어가 있는 명령어에 대해서 체크하는 함수.
*/
char	*cmd_path_in_slash(char *cmd, t_envp *env_c)
{
	char	*cmd_path;
	int		fd;

	cmd_path = NULL;
	errno = 0;
	fd = open(cmd, O_WRONLY);
	if (fd > 0)
		close(fd);
	if (errno != EISDIR)
	{
		if (access(cmd, X_OK) == 0)
		{
			cmd_path = ft_strdup(cmd);
			if (cmd_path == NULL)
				exit(errno);
			return (cmd_path);
		}
	}
	print_strerror(cmd, NULL);
	if (errno == EACCES || errno == EISDIR)
		env_c->last_stat = 126;
	else if (errno == ENOENT)
		env_c->last_stat = 127;
	return (NULL);
}

int	path_in_dot_dot_check(char *cmd, t_envp *env_c)
{
	if (ft_strlen(cmd) == 1 && cmd[0] == '.')
	{
		print_builtin_error(".", NULL, \
		"filename argument required\n.: usage: . filename [arguments]\n");
		env_c->last_stat = 2;
	}
	else if (ft_strlen(cmd) == 2 && cmd[0] == '.' && cmd[1] == '.')
	{
		print_builtin_error(cmd, NULL, "command not found\n");
		env_c->last_stat = 127;
	}
	else
		return (0);
	return (1);
}
