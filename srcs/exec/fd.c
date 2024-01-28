/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:18:12 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/29 00:59:45 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	파일을 열어서 받은 fd값을 통해
	dup2함수를 이용하여 
	TYPE에 맞게 표준입출력으로 방향 전환해주는 함수.
*/
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

/*
	type에 따라 파일을 오픈 하는 방법 분기.
*/
int	open_redirection(t_token *token, int fd)
{
	if (token->type == APPEND)
		fd = open_append(token->str, fd);
	else if (token->type == OUTPUT)
		fd = open_file(token->str, W_OK);
	else if (token->type == INPUT || token->type == HEREDOC)
		fd = open_file(token->str, R_OK);
	return (fd);
}

/*
	리다이렉션할 파일 open 하는 함수.
*/
int	std_to_fd(t_node *std_node)
{
	t_token	*token;
	int		fd;

	fd = 0;
	while (std_node->elem)
	{
		token = std_node->elem;
		if (fd)
			close(fd);
		if (token->str == NULL && token->env_val)
		{
			print_builtin_error(token->env_val, NULL, "ambiguous redirect\n");
			return (-1);
		}
		fd = open_redirection(token, fd);
		if (fd < 0)
			return (-1);
		dup2_to_std(fd, token);
		std_node = std_node->next;
	}
	return (fd);
}

/*
	먼저  parse 연결리스트 안에 있는 pipe 관련 리다이렉션 처리 후,
	각각의 리다이렉션 처리하는 함수.
*/
void	dup_std_fd(t_pinfo *info, t_parse *parse, int i)
{
	int	fd;

	pipe_std_dup(parse->std_lst, info, i);
	fd = std_to_fd(parse->std_lst->head->next);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (info->pipe_cnt)
		pipe_close(info, i);
}
