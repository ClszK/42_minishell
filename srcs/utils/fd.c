/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:18:12 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/25 00:11:28 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_init(t_pinfo *pinfo, int cmd_argc)
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

int	here_doc_process(char *eof)
{
	int		fd;
	char	*tmp_name;

	fd = tmpfile_create(&tmp_name);
	if (fd < 0)
		perror("HEREDOC");
	stdin_heredoc(eof, fd);
	close(fd);
	fd = open_file(tmp_name, R_OK);
	unlink(tmp_name);
	free(tmp_name);
	return (fd);
}

int	dup2_to_std(int fd, t_token *token)
{
	if (token->type == APPEND || token->type == OUTPUT)
	{
		if ((fd && dup2(fd, STDOUT_FILENO) < 0))
			exit(EXIT_FAILURE);
	}
	else if (token->type == HEREDOC || token->type == INPUT)
		if ((fd && dup2(fd, STDIN_FILENO) < 0))
			exit(EXIT_FAILURE);
	return (0);
}

int	std_to_fd(t_node *std_node)
{
	t_token	*token;
	t_node	*std_head;
	int		fd;

	fd = 0;
	std_head = std_node->prev;
	while (std_node->elem)
	{
		token = std_node->elem;
		if (fd)
			close(fd);
		if (token->type == APPEND)
			fd = open_append(token->str);
		else if (token->type == OUTPUT)
			fd = open_file(token->str, W_OK);
		else if (token->type == HEREDOC)
			fd = here_doc_process(token->str);
		else if (token->type == INPUT)
			fd = open_file(token->str, R_OK);
		if (fd < 0)
			return (-1);
		dup2_to_std(fd, token);
		std_node = std_node->next;
	}
	return (fd);
}

int	simple_fd_open(int *fd, t_node *std_node)
{
	fd[STDIN_FILENO] = dup(STDIN_FILENO);
	fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (fd[STDIN_FILENO] < 0 || fd[STDOUT_FILENO] < 0)
	{
		perror("minishell: ");
		return (EXIT_FAILURE);
	}
	fd[FD_IN] = std_to_fd(std_node);
	if (fd[FD_IN] < 0)
		return (EXIT_FAILURE);
	return (0);
}

int	simple_fd_close(int *fd)
{
	if (dup2(fd[STDIN_FILENO], STDIN_FILENO) < 0 || \
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO) < 0)
	{
		perror("minishell: ");
		return (EXIT_FAILURE);
	}
	if (fd[FD_IN])
		close(fd[FD_IN]);
	if (fd[FD_OUT])
		close(fd[FD_OUT]);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	return (0);
}

void	pipe_std_dup(t_stdio *std, t_pinfo *info, int pos)
{
	t_token	*token;

	token = std->head->next->elem;
	if (token && token->type == PIPE_IN)
	{
		if (dup2(info->pfd[(pos - 1) % 2][STDIN_FILENO], STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	token = std->tail->prev->elem;
	if (token && token->type == PIPE_OUT)
		if (dup2(info->pfd[pos % 2][STDOUT_FILENO], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
}

void	dup_std_fd(t_pinfo *info, t_stdio *std_lst, int i)
{
	int	fd[2];

	pipe_std_dup(std_lst, info, i);
	fd[0] = std_to_fd(std_lst->head->next);
	if (fd[0] < 0) 
		exit(EXIT_FAILURE);
	if (info->pipe_cnt)
		pipe_close(info, i);
}
