/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:46:42 by ljh               #+#    #+#             */
/*   Updated: 2024/01/17 22:57:58 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_node(t_node *node)
{
	t_token	*token;

	token = (t_token *)node->elem;	
	if (token && token->type == PIPE)
		return (PIPE);
	return (0);
}

enum e_type	token_redirection_type_change(t_node *node)
{
	t_token		*token;
	t_token		*token_next;

	token = (t_token *)node->elem;
	token_next = (t_token *)node->next->elem;
	if (token_next == NULL)
		return (token->type);
	if (token_next->type != WORD)
		return (token_next->type);
	token_next->type = token->type;
	return (0);
}

enum e_type	analyze_cmd_argc(t_node *token_node, int *cmd_argc)
{
	t_token		*token;
	enum e_type	type;

	*cmd_argc = 0;
	if (is_pipe_node(token_node))
	{
		// if (!token_node->prev->elem || token_node->prev->elem->type== PIPE)
		// 	return (PIPE);
		token_node = token_node->next;
	}
	while (token_node->elem)
	{
		token = token_node->elem;
		if (token->type == WORD)
			*cmd_argc += 1;
		else if (token->type == PIPE)
			break ;
		else
		{
			type = token_redirection_type_change(token_node);
			if (type)
				return (type);
			token_node = token_node->next;
		}
		token_node = token_node->next;
	}
	if (is_pipe_node(token_node))
	{
		if (!token_node->prev->elem)
			return (PIPE);
		token_node = token_node->next;
	}
	printf("cmd_size   : %d\n", *cmd_argc);
	return (0);
}

t_node	*analyze_parse_create(t_analyze *alz, t_node *token_node, int cmd_argc)
{
	t_parse		*parse;
	t_token		*token;
	int		i;

	parse = parse_elem_generate(cmd_argc);
	i = 0;
	errno = 0;
	if (is_pipe_node(token_node))
	{
		parse->stdin_token = (t_token *)token_node->elem;
		token_node = token_node->next;
	}
	while (token_node->elem && !is_pipe_node(token_node))
	{
		token = token_node->elem;
		if (token->type == WORD)
		{
			parse->cmd_argv[i] = ft_strdup(token->str);
			if (parse->cmd_argv[i] == NULL)
				exit(errno);
			i++;
		}
		else
		{
			if (token->type == OUTPUT || token->type == APPEND)
				parse->stdout_token = token;
			else if (token->type == INPUT || token->type == HEREDOC)
				parse->stdin_token = token;
		}
		token_node = token_node->next;
	}
	if (is_pipe_node(token_node))
	{
		if (parse->stdout_token == NULL)
			parse->stdout_token = (t_token *)token_node->elem;
		token_node = token_node->next;
	}
	dlst_add_last(alz, parse);
	return (token_node);
}

int	analyze_start(t_analyze *alz, t_cmdline *cmdline)
{
	t_node		*node;
	int			cmd_argc;
	enum e_type type;

	node = cmdline->head->next;
	while (node->next)
	{
		type = analyze_cmd_argc(node, &cmd_argc);
		if (type)
		{
			printf("Error : %d\n", type);
			return (1);
		}
		node = analyze_parse_create(alz, node, cmd_argc);
		// node = analyze_parse_create(alz, node->elem, cmd_argc);
		// if (node->elem && ((t_token *)node->elem)->type == PIPE)
		// 	node = node->next;
	}
	return (0);
}
