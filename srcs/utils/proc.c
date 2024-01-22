/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:43:21 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/22 15:46:08 by ljh              ###   ########.fr       */
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
			envp[++i] = ft_strdup(map_elem->val);
		if (envp[i] == NULL)
			exit(errno);
		map_node = map_node->next;
	}
	return (envp);
}

void	child_process(t_parse *parse, t_envp *env_c, int i, t_pinfo *info)
{
	char	**envp;

	envp = envp_split(env_c);
	dup_std_fd(info, parse->stdin_lst, parse->stdout_lst, i);
	execve(parse->cmd_path, parse->cmd_argv, envp);
	exit(EXIT_FAILURE);
}