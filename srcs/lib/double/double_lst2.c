/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:28:15 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/08 23:12:32 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_lst.h"

void	*dlst_last_elem(t_node *tail)
{
	return (tail->prev->elem);
}

int	dlst_print(t_node *head, int (*print)(void*))
{
	t_node	*node;

	node = head->next;
	while (node->next)
	{
		if (print(node->elem))
			return (1);
		node = node->next;
	}
	return (0);
}

void	dlst_rev_print(t_node *tail, void (*print)(void*))
{
	t_node	*node;

	node = tail->prev;
	while (node->prev)
	{
		print(node->elem);
		node = node->prev;
	}
}
