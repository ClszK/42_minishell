/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:43:21 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/24 14:14:31 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_pinfo *info, int cmd_cnt)
{
	int	status;
	int	i;

	i = -1;
	while (++i < cmd_cnt)
	{
		info->pid = wait(&status);
		if (info->last_pid == info->pid)
			info->last_status = status;
	}
}

char	*envp_copy(t_map *map)
{
	char	*str;
	size_t	size;

	size = ft_strlen(map->key) + ft_strlen(map->val) + 1;
	str = ft_calloc(sizeof(char), size + 1);
	if (str == NULL)
		exit(errno);
	ft_strlcat(str, map->key, size + 1);
	ft_strlcat(str, "=", size + 1);
	ft_strlcat(str, map->val, size + 1);
	return (str);
}

char	**envp_split(t_envp *env_c)
{
	t_node	*map_node;
	t_map	*map_elem;
	char	**envp;
	int		i;

	errno = 0;
	i = -1;
	envp = ft_calloc(sizeof(char *), (env_c->lst_size + 1));
	if (envp == NULL)
		exit(errno);
	map_node = env_c->head->next;
	while (map_node->elem)
	{
		map_elem = map_node->elem;
		if (map_elem && map_elem->val)
			envp[++i] = envp_copy(map_elem);
		if (envp[i] == NULL)
			exit(errno);
		map_node = map_node->next;
	}
	return (envp);
}

void	child_process(t_parse *parse, t_envp *env_c, int i, t_pinfo *info)
{
	char	**envp;
	int		builtin_idx;

	envp = NULL;
	builtin_idx = is_builtin_command(parse->cmd_path);
	dup_std_fd(info, parse->stdin_lst, parse->stdout_lst, i);
	if (builtin_idx)
		exit(command_excute_builtin(parse, env_c, builtin_idx - 1));
	envp = envp_split(env_c);
	if (parse->cmd_path == NULL)
		exit(env_c->last_stat);
	execve(parse->cmd_path, parse->cmd_argv, envp);
	exit(EXIT_FAILURE);
}