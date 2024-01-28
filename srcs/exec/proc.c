/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:43:21 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/28 22:00:17 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	부모 프로세스가 자식 프로세스들이 끝나길 기다는 함수.
	모든 자식 프로세스가 종료되면 마지막 자식 프로세스 종료 코드를 담고
	사용이 끝난 fd를 닫아줌.
*/
void	wait_child(t_pinfo *info, t_envp *env_c, int cmd_cnt)
{
	int	status;
	int	i;

	i = -1;
	while (++i < cmd_cnt)
	{
		info->pid = wait(&status);
		while (info->pid == -1)
			info->pid = wait(&status);
		if (info->last_pid == info->pid)
			info->last_status = status;
	}
	is_fork_signal(status, info->last_status);
	env_c->last_stat = ((*(int *)&(info->last_status)) >> 8) & 0x000000ff;
	if (info->pipe_cnt)
	{
		close(info->pfd[0][0]);
		close(info->pfd[0][1]);
		close(info->pfd[1][0]);
		close(info->pfd[1][1]);
	}
}

/*
	execve 함수의 두 번째 매개변수는 main에서 받아오는 char **envp 형태가 필요.
	그래서 minishell의 envp을 복사하는 과정.
	여기서는 envp의 한 노드만 복사하는 과정.
*/
char	*envp_copy(t_map *map)
{
	char	*str;
	size_t	size;

	errno = 0;
	size = ft_strlen(map->key) + ft_strlen(map->val) + 1;
	str = ft_calloc(sizeof(char), size + 1);
	if (str == NULL)
		exit(errno);
	ft_strlcat(str, map->key, size + 1);
	ft_strlcat(str, "=", size + 1);
	ft_strlcat(str, map->val, size + 1);
	return (str);
}

/*
	env_c 연결리스트를 char **envp로 복사하는 과정.
*/
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

/*
	자식 프로세스가 실행될 부분.
	여기서 먼저 builtin-command인지 판단하고, 
	리다이렉션을 실행해야할 부분을 진행. 여기서 파이프도 같이 적용됨.
	builtin-command라면 실행후 종료.
	아니면 execve함수가 원하는 형태인 envp를 생성해서
	execve 함수 호출.
*/
void	child_process(t_parse *parse, t_envp *env_c, int i, t_pinfo *info)
{
	char	**envp;
	int		builtin_idx;

	restore_signal();
	envp = NULL;
	builtin_idx = is_builtin_command(parse->cmd_path);
	dup_std_fd(info, parse, i);
	if (builtin_idx)
		exit(command_excute_builtin(parse, env_c, builtin_idx - 1, 1));
	envp = envp_split(env_c);
	if (parse->cmd_path == NULL)
		exit(env_c->last_stat);
	errno = 0;
	execve(parse->cmd_path, parse->cmd_argv, envp);
	exit(errno);
}
