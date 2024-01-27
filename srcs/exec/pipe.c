/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:03:02 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 14:48:38 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	파이프 2개 초기화 함수.
*/
int	pipe_init(t_pinfo *pinfo, int cmd_argc)
{
	if (cmd_argc == 1)
	{
		pinfo->pipe_cnt = 0;
		return (0);
	}
	errno = 0;
	pinfo->pipe_cnt = cmd_argc - 1;
	if (pipe(pinfo->pfd[0]) || pipe(pinfo->pfd[1]))
		return (errno);
	return (0);
}

/*
	읽기 파이프는 0, 쓰기 파이프는 1이다.
	cmd1 | cmd2 형태가 있다고 하면
	cmd1은 pipe[0][1]에다가 출력하고,
	cmd2는 pipe[0][0]으로 출력 값을 읽어온다.
	자식 프로세스에서 사용되지 않는 pipe는 닫아주어야함으로
	사용하지 않는 pipe는 close 한다.
	cmd1 | cmd2 | cmd3이면
	cmd1는	pipe[0][1]
	cmd2는	pipe[0][0]
		    pipe[1][1]
	cmd3는	pipe[1][0]이 필요하다.
*/
void	pipe_close(t_pinfo *info, int pos)
{
	if (pos % 2 == 1)
	{
		close(info->pfd[1][0]);
		close(info->pfd[0][1]);
	}
	else
	{
		close(info->pfd[0][0]);
		close(info->pfd[1][1]);
	}
	if (pos == 0)
		close(info->pfd[1][0]);
	else if (pos == info->pipe_cnt)
		close(info->pfd[pos % 2][1]);
}

/*
	2개의 파이프를 통해 모든 파이프를 연결해주어야하는데
	여기서 사용된 pipe를 close하고 다시 초기화하여
	마치 새롭게 파이프를 생성한 것 처럼 만든다.
*/
void	pipe_parrent_init(t_pinfo *info, int pos)
{
	errno = 0;
	if (pos != 0)
	{
		close(info->pfd[(pos - 1) % 2][0]);
		close(info->pfd[(pos - 1) % 2][1]);
		if (pipe(info->pfd[(pos - 1) % 2]))
			exit(errno);
	}
}

/*
	t_stdio 연결리스트 안에 있는 파이프 처리 함수.
*/
void	pipe_std_dup(t_stdio *std, t_pinfo *info, int pos, int stdin_fd)
{
	t_token	*token;

	token = std->head->next->elem;
	if (stdin_fd == 0 && token && token->type == PIPE_IN)
	{
		if (dup2(info->pfd[(pos - 1) % 2][STDIN_FILENO], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	token = std->tail->prev->elem;
	if (token && token->type == PIPE_OUT)
	{
		if (dup2(info->pfd[pos % 2][STDOUT_FILENO], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
}
