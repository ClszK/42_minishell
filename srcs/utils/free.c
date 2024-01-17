/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:42:10 by ljh               #+#    #+#             */
/*   Updated: 2024/01/17 15:56:38 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_elem_free(void *elem)
{
	t_token	*token;

	token = (t_token *)elem;
	free(token->str);
	free(elem);
}

void	parse_elem_free(void *elem)
{
	t_parse	*parse;
	int		i;

	parse = (t_parse *)elem;
	i = -1;
	while (parse->cmd_argv[++i])
		free(parse->cmd_argv[i]);
	free(parse->cmd_argv);
}