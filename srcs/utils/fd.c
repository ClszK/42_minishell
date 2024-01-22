/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:18:12 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/23 05:37:32 by ljh              ###   ########.fr       */
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

int	std_to_fd(t_stdio *std_lst, int i, int std_fd, t_pinfo *info)
{
	t_node	*std_node;
	t_token	*token;	
	char	*tmp_name;
	int		fd;

	std_node = std_lst->head->next;
	fd = 0;
	while (std_node->elem)
	{
		token = std_node->elem;
		if (token->type == APPEND)
			fd = open(token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (token->type == OUTPUT)
			fd = open_file(token->str, W_OK);
		else if (token->type == HEREDOC)
		{
			fd = tmpfile_create(&tmp_name);
			stdin_heredoc(token->str, fd);
			close(fd);
			fd = open_file(tmp_name, R_OK);
		}
		else if (token->type == INPUT)
			fd = open_file(token->str, R_OK);
		else if (token->type == PIPE)
		{
			if (std_fd == STDIN_FILENO)
				fd = info->pfd[(i - 1) % 2][std_fd];
			else
				fd = info->pfd[i % 2][std_fd];
		}
		if (dup2(fd, std_fd) < 0)
			exit(EXIT_FAILURE);
		std_node = std_node->next;
	}
	return (0);
}

void	dup_std_fd(t_pinfo *info, t_stdio *stdin_lst, t_stdio *stdout_lst, int i)
{
	std_to_fd(stdin_lst, i, STDIN_FILENO, info);
	std_to_fd(stdout_lst, i, STDOUT_FILENO, info);
	if (info->pipe_cnt)
		pipe_close(info, i);
}
