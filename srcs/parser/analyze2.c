/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:51:51 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/26 19:56:55 by ljh              ###   ########.fr       */
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

/*
	cmdline에서 < test라는 부분이 존재하면
	<, test
	연산자, WORD가 될텐데
	여기서 test의 TYPE을 연산자로 변경해주는 작업을 진행한다.
*/
void	token_redirection_type_change(t_node *node)
{
	t_token		*token;
	t_token		*token_next;

	token = (t_token *)node->elem;
	token_next = (t_token *)node->next->elem;
	token_next->type = token->type;
}
