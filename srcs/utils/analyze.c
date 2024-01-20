/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:46:42 by ljh               #+#    #+#             */
/*   Updated: 2024/01/20 06:28:18 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	token = token_node->elem;
	printf("%s\n", token->str);
	if (token->type == WORD)
	{
		parse->cmd_argv[*i] = ft_strdup(token->str);
		if (parse->cmd_argv[*i] == NULL)
			exit(errno);
		*i += 1;
		return (0);
	}
	if (token->type == OUTPUT || token->type == APPEND)
		dlst_add_last(parse->stdout_lst, token_elem_cpy(token_node->next->elem));
	else if (token->type == INPUT || token->type == HEREDOC)
		dlst_add_last(parse->stdin_lst, token_elem_cpy(token_node->next->elem));
	return (1);
}

t_node	*analyze_parse_create(t_analyze *alz, t_node *token_node, \
								t_parse *parse)
{
	int			i;

	i = 0;
	errno = 0;
	if (is_pipe_node(token_node))
	{
		dlst_add_last(parse->stdin_lst, token_elem_cpy(token_node->elem));
		token_node = token_node->next;
	}
	while (token_node->elem && !is_pipe_node(token_node))
	{
		if (analyze_token_parse(token_node, parse, &i))
			token_node = token_node->next;
		token_node = token_node->next;
	}
	if (is_pipe_node(token_node))
		dlst_add_last(parse->stdout_lst, token_elem_cpy(token_node->elem));
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
