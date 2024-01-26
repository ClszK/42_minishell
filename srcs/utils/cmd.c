/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/26 18:56:53 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	
	명령어 전처리.
	token화, 구문 분석, 변수 확장, 파일 확장.
*/
int	command_preprocessing(t_shinfo *sh)
{
	int		error_token;

	error_token = valid_quote(sh->rline);
	if (!error_token)
	{
		token_cmdline(sh->rline, &(sh->cmdline));
		if (sh->cmdline.lst_size == 0)
			return (1);
		error_token = analyze_start(&sh->alz, &sh->cmdline);
		if (!error_token)
		{
			expand_start(&sh->alz, &sh->env_c);
			path_insert_in_parse(&sh->alz, &sh->env_c);
		}
	}
	if (error_token)
	{
		sh->env_c.last_stat = 258;
		print_syntax_error(error_token);
		return (1);
	}
	return (0);
}

/*
	builtin command 실행 후 exit code 반환
*/
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

/*
	error message 수정 필요
*/
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
			pipe(info.pfd[(i - 1) % 2]);
		}
		info.last_pid = info.pid;
		parse_node = parse_node->next;
	}
	wait_child(&info, env_c, i);
}

int	command_simple_exec(t_parse *parse, t_envp *env_c, int builtin_idx)
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

/*
int	_command_preprocessing(t_shinfo *sh)
{
	int		error_token;

	if (sh->rline && *(sh->rline) != '\0')
	{
		error_token = valid_quote(sh->rline);
		if (error_token)
		{
			sh->env_c.last_stat = 258;
			print_syntax_error(error_token);
			return (1);
		}
		token_cmdline(sh->rline, &(sh->cmdline));
		if (sh->cmdline.lst_size != 0)
		{
			error_token = analyze_start(&sh->alz, &sh->cmdline);
			if (error_token)
			{
				sh->env_c.last_stat = 258;
				print_syntax_error(error_token);
				return (1);
			}
			expand_start(&sh->alz, &sh->env_c);
			path_insert_in_parse(&sh->alz, &sh->env_c);
		}
		return (0);
	}
	return (1);
}
*/