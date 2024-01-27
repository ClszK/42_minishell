/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 19:35:53 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	
	명령어 전처리.
	token화, 구문 분석, 변수 확장, 파일 확장.
	먼저, 따옴표의 처리가 쌍으로 되어있는지 체크.
	cmdline의 크기가 0이면, 즉, token화가 된게 없다면 엔터나 공백만 존재하기 때문에 종료.
	그리고 token화한 cmdline을 분석 시작하고,
	분석하다가 에러가 발생한 token에 대해 반환하고 종료.
	아니면 분석이 끝난 t_analyze 연결리스트를 가지고 expand 시작.
	expand는 $ 확장 영역.
	이후 명령어 확장 영역 수행한다.
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
		error_token = analyze_start(&sh->alz, &sh->cmdline, &sh->heredoc);
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
	Pipe로 연결된 명령어들은 자식 프로세스에서 해당 명령어 실행해야함.
	Fork 함수를 통해 자식 프로세스를 생성 후, 
	실행할 명령어가 builtin-command인지, 아닌지 판단 후,
	builtin-command이면 작성한 builtin 실행
	아니면 execve 함수를 통해서 명령어 실행.
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
		pipe_parrent_init(&info, i);
		info.last_pid = info.pid;
		parse_node = parse_node->next;
	}
	wait_child(&info, env_c, i);
}

/*
	builtin-command 실행부.
	여기서 리다이렉션이 있는 경우도 함께 처리.
	만약 리다이렉션으로 인해 표준 입출력이 dup2를 통해 복제가 된다면,
	되돌려주는 작업도 같이함.
*/
int	command_simple_exec(t_parse *parse, t_envp *env_c, int builtin_idx)
{
	int	fd[3];
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

/*
	command를 실행하는 함수.
	여기서 pipe로 연결된 command_line인지 판단.
	pipe로 연결되어 있지 않더라도 builtin-command가 아니라면
	fork 후 execve함수를 통해 실행해야함.
*/
void	command_excute(t_analyze *alz, t_envp *env_c, t_stdio *heredoc)
{
	t_parse		*parse;
	int			builtin_idx;

	if (heredoc->lst_size)
		heredoc_process(heredoc);
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