/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:35:39 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 02:26:05 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	명령어 경로를 cmd_path에 담는 함수.
*/
char	*path_cmd_path(char *cmd, t_envp *env_c)
{
	char	**path;
	char	*cmd_path;

	if (cmd == NULL)
		return (NULL);
	errno = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd_path_in_slash(cmd, env_c));
	if (path_in_dot_dot_check(cmd, env_c))
		return (NULL);
	path = path_find_in_env(env_c);
	cmd_path = path_cmd_valid(path, cmd);
	split_free(path);
	if (cmd_path)
		return (cmd_path);
	print_cmd_path_error(cmd, env_c);
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
