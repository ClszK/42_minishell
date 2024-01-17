/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:51:51 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/18 02:54:28 by jeholee          ###   ########.fr       */
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

void	token_redirection_type_change(t_node *node)
{
	t_token		*token;
	t_token		*token_next;

	token = (t_token *)node->elem;
	token_next = (t_token *)node->next->elem;
	token_next->type = token->type;
}
