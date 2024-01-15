/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:46:42 by ljh               #+#    #+#             */
/*   Updated: 2024/01/16 02:56:10 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_pipe(t_token *token)
{
	if (token->type == PIPE)
		return (PIPE);
	return (0);
}

int	analyze_token_size(t_node *token_node)
{
	t_token	*token;
	int		token_size;
	int		cmd_argc;

	token_size = 0;
	cmd_argc = 0;
	while (token_node->next)
	{
		token = token_node->elem;
		if (token->type == WORD)
			cmd_argc++;
		/* newline or pipe */
		if (token_is_pipe_newline(token))
		{
			printf("token_size : %d\n", token_size);
			printf("cmd_size   : %d\n", cmd_argc);
			break ;
		}
		token_size++;
		token_node = token_node->next;
	}
	if (token_size == 0)
		return (0);
	return (cmd_argc);
}

int	analyze_start(t_analyze *alz, t_cmdline *cmdline)
{
	t_node	*node;
	int		cmd_argc;

	node = cmdline->head->next;
	while (node->next)
	{
		cmd_argc = analyze_token_size(node);
		if (!cmd_argc)
			return (1);
	}
}

void	analyze_parse_create(t_analyze *alz, t_node *token_node, int cmd_argc)
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
		}
		/* newline or pipe */
		if (token_is_pipe_newline(token))
		{
			break ;
		}
		token_node = token_node->next;
	}
}