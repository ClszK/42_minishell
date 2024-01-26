/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:10:30 by ljh               #+#    #+#             */
/*   Updated: 2024/01/26 22:12:23 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	필요한 fd를 여는 작업.
	여기서 리다이렉션이 있는 경우, 처리함.
	표준 입출력이 dup2함수를 통해 변화했을 경우,
	builtin-command 실행 후 되돌려주는 작업을 진행해야해서
	dup함수를 통해 원본 저장.
	swap 함수를 구현할 때 tmp에다가 원본 값 저장하는 원리와 동일.
*/
int	simple_fd_open(int *fd, t_parse *parse)
{
	errno = 0;
	fd[STDIN_FILENO] = dup(STDIN_FILENO);
	fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (fd[STDIN_FILENO] < 0 || fd[STDOUT_FILENO] < 0)
	{
		perror("minishell: ");
		return (EXIT_FAILURE);
	}
	fd[2] = std_to_fd(parse->here_doc_lst->head->next);
	if (fd[2] < 0)
		return (EXIT_FAILURE);
	fd[3] = std_to_fd(parse->std_lst->head->next);
	if (fd[3] < 0)
		return (EXIT_FAILURE);
	return (0);
}

/*
	사용이 끝난 fd를 닫아주는 함수.
*/
int	simple_fd_close(int *fd)
{
	errno = 0;
	if (dup2(fd[STDIN_FILENO], STDIN_FILENO) < 0 || \
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO) < 0)
	{
		perror("minishell: ");
		return (EXIT_FAILURE);
	}
	if (fd[2])
		close(fd[2]);
	if (fd[3])
		close(fd[3]);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	return (0);
}
