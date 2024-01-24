/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/24 18:03:44 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* builtin command 실행 후 fd 닫기 로직 만들기. */
int	command_excute_builtin(t_parse *parse, t_envp *env_c, int builtin_idx)
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
		exit_code = builtin_exit(parse);
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

void	command_excute(t_analyze *alz, t_envp *env_c)
{
	t_parse		*parse;
	int			builtin_idx;
	int			fd[4];

	if (is_include_pipe(alz))
		command_fork(alz, env_c);
	else
	{
		parse = alz->head->next->elem;
		builtin_idx = 0;
		if (parse->cmd_path)
			builtin_idx = is_builtin_command(parse->cmd_path);
		if (parse->cmd_path && builtin_idx)
		{
			fd[STDIN_FILENO] = dup(STDIN_FILENO);
			fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
			fd[FD_IN] = std_to_fd(parse->stdin_lst->head->next, 0, STDIN_FILENO, NULL);
			if (fd[FD_IN] > 0)
			{
				if (dup2(fd[FD_IN], STDIN_FILENO) < 0)
					exit(EXIT_FAILURE);
			}
			fd[FD_OUT] = std_to_fd(parse->stdout_lst->head->next, 0, STDOUT_FILENO, NULL);
			if (fd[FD_OUT] > 0)
			{
				if (dup2(fd[FD_OUT], STDOUT_FILENO) < 0)
					exit(EXIT_FAILURE);
			}
			env_c->last_stat = command_excute_builtin(parse, env_c, builtin_idx - 1);
			dup2(fd[STDIN_FILENO], STDIN_FILENO);
			dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
			if (fd[FD_IN])
				close(fd[FD_IN]);
			if (fd[FD_OUT])
				close(fd[FD_OUT]);
			close(fd[STDIN_FILENO]);
			close(fd[STDOUT_FILENO]);
		}
		else
			command_fork(alz, env_c);
	}
}

// heredoc 임시파일 즉시 삭제.

// builtin command fd 닫기