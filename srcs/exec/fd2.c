/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:10:30 by ljh               #+#    #+#             */
/*   Updated: 2024/01/28 23:58:35 by jeholee          ###   ########.fr       */
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
	fd[2] = std_to_fd(parse->std_lst->head->next);
	if (fd[2] < 0)
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
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	return (0);
}

int	heredoc_process(t_node *heredoc_node, t_envp *env_c, int status, int tmp_fd)
{
	t_token	*heredoc;
	pid_t	pid;
	char	*tmp_name;

	signal(SIGINT, SIG_IGN);
	while (heredoc_node->elem)
	{
		heredoc = heredoc_node->elem;
		tmp_fd = tmpfile_create(&tmp_name);
		pid = fork();
		if (pid < 0)
			perror_exit("minishell");
		else if (pid == 0)
			child_heredoc_process(heredoc->str, tmp_fd);
		wait(&status);
		close(tmp_fd);
		free(heredoc->str);
		signal(SIGINT, sigint_handler);
		env_c->last_stat = ((*(int *)&(status)) >> 8) & 0x000000ff;
		if (env_c->last_stat == 1)
			return (1);
		heredoc->str = tmp_name;
		heredoc_node = heredoc_node->next;
	}
	return (0);
}
