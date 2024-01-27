/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:28:15 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 19:43:01 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_lst.h"

void	*dlst_last_elem(struct s_lst *lst)
{
	return (lst->tail->prev->elem);
}

int	dlst_print(struct s_lst *lst, int (*print)(void*))
{
	t_node	*node;

	node = lst->head->next;
	while (node->next)
	{
		if (print(node->elem))
			return (1);
		node = node->next;
	}
	return (0);
}

void	dlst_rev_print(struct s_lst *lst, void (*print)(void*))
{
	t_node	*node;

	node = lst->tail->prev;
	while (node->prev)
	{
		print(node->elem);
		node = node->prev;
	}
}

int	dlst_delete(struct s_lst *lst, \
					void (*del)(void*), int (*find)(void*, void*), void *cmp)
{
	t_node	*del_node;

	del_node = lst->head->next;
	while (del_node->next)
	{
		if (find(del_node->elem, cmp))
		{
			del(del_node->elem);
			del_node->next->prev = del_node->prev;
			del_node->prev->next = del_node->next;
			free(del_node);
			lst->lst_size--;
			return (0);
		}
		del_node = del_node->next;
	}
	return (1);
}
