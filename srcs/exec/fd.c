/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:18:12 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 15:20:56 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	here_doc 처리하는 함수.
*/
int	here_doc_fork(t_stdio *heredoc, char *eof)
{
	int		fd;
	char	*tmp_name;
	t_pinfo	info;
	t_node	*node;

	node = heredoc->head->next;
	while (node->elem)
	{
		errno = 0;
		info.pid = fork();
		if (info.pid < 0)
			perror_exit("minishell");
		else if (info.pid == 0)
			here_doc_process(eof);
		pipe_parrent_init(&info, i);
		node = node->next;
	}
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
	else if (token->type == HEREDOC)
		fd = here_doc_process(token->str);
	else if (token->type == INPUT)
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
	int	fd[2];

	fd[0] = std_to_fd(parse->here_doc_lst->head->next);
	if (fd[0] < 0)
		exit(EXIT_FAILURE);
	printf("i : %d\nfd[0] : %d\n",i, fd[0]);
	printf("STD_LST\n");
	dlst_print(parse->std_lst, test_printf_token);
	printf("HERE_DOC\n");
	dlst_print(parse->here_doc_lst, test_printf_token);
	pipe_std_dup(parse->std_lst, info, i, fd[0]);
	fd[1] = std_to_fd(parse->std_lst->head->next);
	if (fd[1] < 0)
		exit(EXIT_FAILURE);
	if (info->pipe_cnt)
		pipe_close(info, i);
}
