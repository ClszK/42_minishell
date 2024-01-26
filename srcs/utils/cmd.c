/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/26 15:10:35 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* builtin command 실행 후 fd 닫기 로직 만들기. */
int	command_excute_builtin(t_parse *parse, t_envp *env_c, \
							int builtin_idx, int is_fork)
{
	int	exit_code;

	exit_code = 0;
	if (builtin_idx == 0)
		exit_code = builtin_cd(parse, env_c);
	else if (builtin_idx == 1)
		exit_code = builtin_echo(parse);
	else if (builtin_idx == 2)
		exit_code = builtin_env(env_c);
	else if (builtin_idx == 3)
		exit_code = builtin_exit(parse, is_fork);
	else if (builtin_idx == 4)
		exit_code = builtin_export(parse, env_c);
	else if (builtin_idx == 5)
		exit_code = builtin_pwd(env_c);
	else if (builtin_idx == 6)
		exit_code = builtin_unset(parse, env_c);
	return (exit_code);
}

/* error message 수정 필요 */
void	command_fork(t_analyze *alz, t_envp *env_c)
{
	int			i;
	t_node		*parse_node;
	t_pinfo		info;
	
	parse_node = alz->head->next;
	if (pipe_init(&info, alz->lst_size))
		exit(errno);
	i = -1;
	while (++i < alz->lst_size)
	{
		errno = 0;
		info.pid = fork();
		if (info.pid < 0)
			perror_exit("minishell");
		else if (info.pid == 0)
			child_process(parse_node->elem, env_c, i, &info);
		if (i != 0)
		{
			close(info.pfd[(i - 1) % 2][0]);
			close(info.pfd[(i - 1) % 2][1]);
			pipe(info.pfd[(i-1)%2]);
		}
		info.last_pid = info.pid;
		parse_node = parse_node->next;
	}
	if (info.pipe_cnt)
	{
		close(info.pfd[0][0]);
		close(info.pfd[0][1]);
		close(info.pfd[1][0]);
		close(info.pfd[1][1]);
	}
	wait_child(&info, i);
	env_c->last_stat = ((*(int *)&(info.last_status)) >> 8) & 0x000000ff;
}

int		command_simple_exec(t_parse *parse, t_envp *env_c, int builtin_idx)
{
	int	fd[4];
	int	stat;
	int	fd_stat;

	stat = 0;
	fd_stat = simple_fd_open(fd, parse);
	if (fd_stat)
	{
		stat = simple_fd_close(fd);
		if (stat)
			return (stat);
		return (fd_stat);
	}
	stat = command_excute_builtin(parse, env_c, builtin_idx - 1, 0);
	fd_stat = simple_fd_close(fd);
	if (fd_stat)
		return (fd_stat);
	return (stat);
}

void	command_excute(t_analyze *alz, t_envp *env_c)
{
	t_parse		*parse;
	int			builtin_idx;

	if (is_include_pipe(alz))
		command_fork(alz, env_c);
	else
	{
		parse = alz->head->next->elem;
		builtin_idx = is_builtin_command(parse->cmd_path);
		if (builtin_idx)
			env_c->last_stat = command_simple_exec(parse, env_c, builtin_idx);
		else
			command_fork(alz, env_c);
	}
}

// heredoc 임시파일 즉시 삭제.

// builtin command fd 닫기