/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/23 09:17:12 by ljh              ###   ########.fr       */
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

void	command_excute(t_shinfo *sh)
{
	t_analyze	*alz;
	t_parse		*parse;
	t_envp		*env_c;
	int			builtin_idx;
	int			stdin_fd;
	int			stdout_fd;
	int			fd1;
	int			fd2;


	alz = &sh->alz;
	env_c = &sh->env_c;
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
			stdin_fd = dup(STDIN_FILENO);
			stdout_fd = dup(STDOUT_FILENO);
			fd1 = std_to_fd(parse->stdin_lst, 0, STDIN_FILENO, NULL);
			fd2 = std_to_fd(parse->stdout_lst, 0, STDOUT_FILENO, NULL);
			env_c->last_stat = command_excute_builtin(parse, env_c, builtin_idx - 1);
			dup2(stdin_fd, STDIN_FILENO);
			dup2(stdout_fd, STDOUT_FILENO);
			if (fd1)
				close(fd1);
			if (fd2)
				close(fd2);
			close(stdin_fd);
			close(stdout_fd);
		}
		else
			command_fork(alz, env_c);
	}
}

// heredoc 임시파일 즉시 삭제.

// builtin command fd 닫기