/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:43:32 by ljh               #+#    #+#             */
/*   Updated: 2024/01/20 06:26:40 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_elem_generate(char *str, enum e_type type)
{
	t_token	*node;

	errno = 0;
	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		exit(errno);
	node->str = str;
	node->type = type;
	return (node);
}

t_token	*token_elem_cpy(void *elem)
{
	t_token *node;
	t_token *token;
	char	*str;

	errno = 0;
	token = elem;
	str = NULL;
	if (token->str)
	{
		str = ft_strdup(token->str);
		if (str == NULL)
			exit(errno);
	}
	node = token_elem_generate(str, token->type);
	return (node);
}

t_parse	*parse_elem_generate(int cmd_argc)
{
	t_parse	*node;

	errno = 0;
	node = (t_parse *)malloc(sizeof(t_parse));
	if (node == NULL)
		exit(errno);
	node->cmd_argc = cmd_argc;
	node->cmd_argv = (char **)malloc(sizeof(char *) * (cmd_argc + 1));
	if (node->cmd_argv == NULL)
		exit(errno);
	ft_memset(node->cmd_argv, 0, sizeof(char *) * (cmd_argc + 1));
	node->cmd_path = NULL;
	node->stdin_lst = stdio_init();
	node->stdout_lst = stdio_init();
	return (node);
}
