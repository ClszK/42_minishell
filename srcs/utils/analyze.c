/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:46:42 by ljh               #+#    #+#             */
/*   Updated: 2024/01/17 14:48:24 by ljh              ###   ########.fr       */
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

int	analyze_cmd_argc(t_node *token_node)
{
	t_token	*token;
	t_token	*token_prev;
	int		cmd_argc;
	int		token_cnt;

	cmd_argc = 0;
	token_cnt = 0;
	while (token_node->next)
	{
		token = token_node->elem;
		token_prev = token_node->prev->elem;
		if (token->type == WORD)
		{
			if (token_prev == NULL || token_prev->type == WORD)
				cmd_argc++;
		}
		else if (token_prev->type != WORD)
			return (-1);
		if (token->type == PIPE)
			break ;
		token_cnt++;
		token_node = token_node->next;
	}
	printf("token_size : %d\n", token_cnt);
	printf("cmd_size   : %d\n", cmd_argc);
	if (token_cnt == 0)
		return (-1);
	return (cmd_argc);
}

t_node	*analyze_parse_create(t_analyze *alz, t_node *token_node, int cmd_argc)
{
	t_parse	*parse;
	t_token	*token;
	int		i;

	parse = parse_elem_generate(cmd_argc);
	i = 0;
	errno = 0;
	while (token_node->next)
	{
		token = token_node->elem;
		if (token->type == WORD)
		{
			parse->cmd_argv[i] = ft_strdup(token->str);
			if (parse->cmd_argv[i] == NULL)
				exit(errno);
			i++;
		}
		else if (token->type == OUTPUT || token->type == APPEND)
			parse->stdout_token = token;
		else if (token->type == INPUT || token->type == HEREDOC)
			parse->stdin_token = token;
		/* newline or pipe */
		if (is_pipe_node(token))
		{
			dlst_add_last(alz, parse);
			return (token_node);
		}
		token_node = token_node->next;
	}
}

int	analyze_start(t_analyze *alz, t_cmdline *cmdline)
{
	t_node	*node;
	int		cmd_argc;

	node = cmdline->head->next;
	while (node->next)
	{
		cmd_argc = analyze_cmd_argc(node);
		if (cmd_argc < 0)
		{
			printf("Error\n");
			return (1);
		}
		for (int x = 0; x < cmd_argc; x++)
			node = node->next;
		// if (((t_token *)node->elem)->type == PIPE)
		// 	node = node->next;
		// node = analyze_parse_create(alz, node->elem, cmd_argc);
	}
}