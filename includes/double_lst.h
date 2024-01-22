/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 23:59:03 by ljh               #+#    #+#             */
/*   Updated: 2024/01/21 07:40:52 by jeholee          ###   ########.fr       */
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

struct s_lst
{
	t_node	*head;
	t_node	*tail;
	long	lst_size;
	char	*pwd;
};

t_node	*dlst_node_generate(void *element);
int		dlst_init(struct s_lst *lst);
int		dlst_add_last(struct s_lst *lst, void *element);
void	dlst_del_last(struct s_lst *lst, void (*del)(void*));
void	dlst_del_all(struct s_lst *lst, void (*del)(void*));
void	*dlst_last_elem(struct s_lst *lst);
int		dlst_print(struct s_lst *lst, int (*print)(void*));
void	dlst_rev_print(struct s_lst *lst, void (*print)(void*));
int		dlst_delete(struct s_lst *lst, \
					void (*del)(void*), int (*find)(void*, void*), void *cmp);

#endif