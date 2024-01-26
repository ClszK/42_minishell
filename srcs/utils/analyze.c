/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:46:42 by ljh               #+#    #+#             */
/*   Updated: 2024/01/26 19:40:29 by ljh              ###   ########.fr       */
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

int	analyze_token_parse(t_node *token_node, t_parse *parse, int *i)
{
	t_token		*token;

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
	if (token->type == OUTPUT || token->type == APPEND || token->type == INPUT)
		dlst_add_last(parse->std_lst, \
						token_elem_cpy(token_node->next->elem, token->type));
	else if (token->type == HEREDOC)
		dlst_add_last(parse->here_doc_lst, \
						token_elem_cpy(token_node->next->elem, token->type));
	return (1);
}


t_node	*analyze_parse_create(t_analyze *alz, t_node *token_node, \
								t_parse *parse)
{
	int	i;

	i = 0;
	if (is_pipe_node(token_node))
	{
		dlst_add_last(parse->std_lst, token_elem_cpy(token_node->elem, PIPE_IN));
		token_node = token_node->next;
	}
	while (token_node->elem && !is_pipe_node(token_node))
	{
		if (analyze_token_parse(token_node, parse, &i))
			token_node = token_node->next;
		token_node = token_node->next;
	}
	if (is_pipe_node(token_node))
		dlst_add_last(parse->std_lst, token_elem_cpy(token_node->elem, PIPE_OUT));
	dlst_add_last(alz, parse);
	return (token_node);
}

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
int	analyze_start(t_analyze *alz, t_cmdline *cmdline)
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
		node = analyze_parse_create(alz, node, parse);
	}
	return (0);
}
