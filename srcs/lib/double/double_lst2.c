/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:28:15 by jeholee           #+#    #+#             */
/*   Updated: 2023/11/01 21:29:24 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_lst.h"

void	*dlst_last_elem(t_node *tail)
{
	return (tail->prev->elem);
}

void	dlst_print(t_node *head, void (*print)(void*))
{
	t_node	*node;

	node = head->next;
	while (node->next)
	{
		print(node->elem);
		node = node->next;
	}
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
