/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 11:31:07 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/25 05:23:00 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			perror_exit("minishell");
		return (path);
	}
	return (NULL);
}

char	*path_cmd(char *path, char *cmd)
{
	char	*rcmd;
	char	*tmp;

	errno = 0;
	rcmd = ft_strjoin(path, "/");
	if (rcmd == NULL && errno != 0)
		perror_exit("minishell");
	tmp = rcmd;
	rcmd = ft_strjoin(rcmd, cmd);
	free(tmp);
	if (rcmd == NULL && errno != 0)
		perror_exit("minishell");
	return (rcmd);
}

char	*path_cmd_valid(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = -1;
	if (path == NULL)
		return (NULL);
	while (path[++i] && *cmd)
	{
		cmd_path = path_cmd(path[i], cmd);
		if ((access(cmd_path, X_OK) == 0))
			return (cmd_path);
		if (errno == EACCES)
			break ;
		errno = 0;
		free(cmd_path);
	}
	return (NULL);
}

char	*path_cmd_path(char *cmd, t_envp *env_c)
{
	char	**path;
	char	*cmd_path;

	if (cmd == NULL)
		return (NULL);
	cmd_path = NULL;
	path = path_find_in_env(env_c);
	if (ft_strchr(cmd, '/'))
	{
		open(cmd, O_WRONLY);
		if (errno == EACCES || errno == EISDIR)
		{
			print_strerror(cmd, NULL);
			env_c->last_stat = 126;
			return (NULL);
		}
		if (access(cmd, X_OK) == 0)
		{
			cmd_path = ft_strdup(cmd);
			if (cmd_path == NULL)
				exit(errno);
			return (cmd_path);
		}
		else
		{
			print_strerror(cmd, NULL);
			env_c->last_stat = 127;
			return (NULL);
		}
		
	}
	else
		cmd_path = path_cmd_valid(path, cmd);
	split_free(path);
	if (cmd_path)
		return (cmd_path);
	if (errno == EACCES)
	{
		print_strerror(cmd, NULL);
		env_c->last_stat = 126;
	}
	else
	{
		print_builtin_error(cmd, NULL, "command not found\n");
		env_c->last_stat = 127;
	}
	return (NULL);
}

void	path_insert_in_parse(t_analyze *alz, t_envp *env_c)
{
	t_node	*parse_node;
	t_parse	*parse;

	parse_node = alz->head->next;
	while (parse_node->elem)
	{
		parse = parse_node->elem;
		if (parse->cmd_argv && parse->cmd_argv[0])
		{
			if (is_builtin_command(parse->cmd_argv[0]))
				parse->cmd_path = ft_strdup(parse->cmd_argv[0]);
			else
				parse->cmd_path = path_cmd_path(parse->cmd_argv[0], env_c);
		}
		parse_node = parse_node->next;
	}
}