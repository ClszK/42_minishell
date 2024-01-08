/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminpar <suminpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 23:59:03 by ljh               #+#    #+#             */
/*   Updated: 2024/01/08 07:16:47 by suminpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_LST_H
# define DOUBLE_LST_H

# include "../srcs/lib/libft/libft.h"
# include <stdlib.h>

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	void			*elem;
}	t_node;

t_node	*dlst_node_generate(void *element);
int		dlst_init(t_node **head, t_node **tail);
int		dlst_add_last(t_node *tail, void *element);
void	dlst_del_last(t_node *tail, void (*del)(void*));
void	*dlst_last_elem(t_node *tail);
int		dlst_print(t_node *head, int (*print)(void*));
void	dlst_rev_print(t_node *tail, void (*print)(void*));
void	dlst_del_all(t_node *head, void (*del)(void*));

#endif