/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:46:42 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 19:38:41 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cmdline 연결리스트 안에 몇 개의 명령어가 있는지 확인하는 함수.
	예를 들어, ls -al | grep test | cat -e 인 경우,
	ls  , -al ,  |  , grep, test,  |  , cat , -e
 	WORD, WORD, PIPE, WORD, WORD, PIPE, WORD, WORD
	형태로 각각의 노드가 입력되어 있을 텐데, 
	파이프를 기준으로 cmd_argc 체크.
	처음에는 ls -al | 까지 체크하는데 cmd_argc는 2가 됨.(반환)
	그 다음에 이 함수가 호출되면 | grep test | 까지 체크되고 cmd_argc는 2가됨.(반환)
	마지막으로 | cat -e 하고 cmd_argc 값을 2로 반환.
*/
int	analyze_cmd_argc(t_node *token_node)
{
	t_token		*token;
	int			cmd_argc;

	cmd_argc = 0;
	if (is_pipe_node(token_node) == PIPE)
		token_node = token_node->next;
	while (token_node->elem)
	{
		token = token_node->elem;
		if (token->type == WORD)
			cmd_argc += 1;
		else if (token->type == PIPE)
			break ;
		else
		{
			token_redirection_type_change(token_node);
			token_node = token_node->next;
		}
		token_node = token_node->next;
	}
	if (is_pipe_node(token_node) == PIPE)
		token_node = token_node->next;
	return (cmd_argc);
}

/*
	PIPE를 제외한 나머지 노드들에 대한 노드를 분석하고 담아둔다.
	TYPE이 WORD이면 cmd_argv에 담아두고,
	TYPE이 파이프를 제외한 연산자이면 stdio에 추가하는데 여기서
	here_doc만 따로 here_doc 연결리스트에 담고 나머지는 stdio에 담는다.
*/
int	analyze_token_parse(t_node *token_node, t_parse *parse, \
							int *i, t_stdio *heredoc)
{
	t_token		*token;
	t_token		*token_cpy;

	errno = 0;
	token = token_node->elem;
	if (token->type == WORD)
	{
		parse->cmd_argv[*i] = ft_strdup(token->str);
		if (parse->cmd_argv[*i] == NULL)
			exit(errno);
		*i += 1;
		return (0);
	}
	token_cpy = token_elem_cpy(token_node->next->elem, token->type);
	dlst_add_last(parse->std_lst, token_cpy);
	if (token->type == HEREDOC)
		dlst_add_last(heredoc, token_cpy);
	return (1);
}

/*
	parse를 생성하는 함수.
	예를 들어, ls -al | grep test < hi| cat -e 이면,
	처음엔 cmd_argv에 ls, -al이 담기고
	stdio 에는 type이 PIPEOUT이 담긴다. 이유는 ls -al | 이기 때문에.
	두 번째는 cmd_argv에 grep, test가 담기고
	stdio에는 PIPEIN, PIPEOUT, < 가 담긴다.
	세 번째는 cmd_argv에 cat, -e가 담기고
	stdio는 PIPEIN이 담긴다.
*/
t_node	*analyze_parse_create(t_analyze *alz, t_node *token_node, \
								t_parse *parse, t_stdio *heredoc)
{
	int	i;

	i = 0;
	if (is_pipe_node(token_node))
	{
		dlst_add_last(parse->std_lst, \
				token_elem_cpy(token_node->elem, PIPE_IN));
		token_node = token_node->next;
	}
	while (token_node->elem && !is_pipe_node(token_node))
	{
		if (analyze_token_parse(token_node, parse, &i, heredoc))
			token_node = token_node->next;
		token_node = token_node->next;
	}
	if (is_pipe_node(token_node))
		dlst_add_last(parse->std_lst, \
				token_elem_cpy(token_node->elem, PIPE_OUT));
	dlst_add_last(alz, parse);
	return (token_node);
}

/*
	구문 분석을 통해 오류가 나는 부분 찾는 함수.
	첫 번째 노드와 마지막 노드가 파이프인 경우,
	리다이렉션인데 이전 노드도 리다이렉션인 경우,
	파이프인데 이전 노드가 연산자(|, <, <<, >, >>)인 경우,
	마지막 노드가 연산자인 경우
	해당 Type 반환
*/
enum e_type	analyze_syntax_valid(t_cmdline *cmdline)
{
	t_node		*token_node;
	t_token		*token;
	t_token		*token_prev;

	token_node = cmdline->head->next;
	if (((t_token *)(token_node->elem))->type == PIPE)
		return (PIPE);
	while (token_node->elem)
	{
		token = token_node->elem;
		token_prev = token_node->prev->elem;
		if (is_redirect(token) && token_prev && is_redirect(token_prev))
			return (token->type);
		if (token->type == PIPE && token_prev && token_prev->type != WORD)
			return (token->type);
		token_node = token_node->next;
	}
	if (((t_token *)(token_node->prev->elem))->type != WORD)
		return (NEWLN);
	return (NONE);
}

/*
	앞에서 token화를 진행한 결과가 담긴 cmdline 연결리스트를 구문 분석하는 함수.
	처음에 syntax가 오류일 때를 체크함.
	이후 cmdline을 순회하면서 로직 실행.
*/
int	analyze_start(t_analyze *alz, t_cmdline *cmdline, t_stdio *heredoc)
{
	t_node		*node;
	t_parse		*parse;
	int			cmd_argc;
	enum e_type	type;

	type = analyze_syntax_valid(cmdline);
	if (type)
		return (type);
	node = cmdline->head->next;
	while (node->next)
	{
		cmd_argc = analyze_cmd_argc(node);
		parse = parse_elem_generate(cmd_argc);
		node = analyze_parse_create(alz, node, parse, heredoc);
	}
	if (heredoc->lst_size > 16)
	{
		print_builtin_error(NULL, NULL, \
						"maximum here-document count exceeded\n");
		exit(2);
	}
	return (0);
}
