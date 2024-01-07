/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:05:35 by stack             #+#    #+#             */
/*   Updated: 2023/09/15 01:09:58 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	// 에러 제거

t_list_g	*gnl_lstnew(char *content)
{
	t_list_g	*node;
	long long	i;
	long long	lnpos;

	i = -1;
	lnpos = -1;
	node = (t_list_g *)malloc(sizeof(t_list_g));
	if (node == NULL)
		return (NULL);
	while (content[++i])
		if (content[i] == '\n' && lnpos == -1)
			lnpos = i + 1;
	node->content = gnl_strncat((char *)malloc(i + 1), content, i + 1, 1);
	if (node->content == NULL)
	{
		free(node);
		return (NULL);
	}
	node->len = i;
	node->totallen = i;
	node->lnpos = lnpos;
	node->next = NULL;
	return (node);
}

int	gnl_lstadd_back(t_list_g **lst, t_list_g *new)
{
	t_list_g	*node;

	node = *lst;
	if (new == NULL)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new;
		return (1);
	}
	while (node->next)
		node = node->next;
	new->totallen += node->totallen;
	node->next = new;
	return (1);
}

void	gnl_lstclear(t_list_g **lst, char *str)
{
	t_list_g	*node;

	if (lst == NULL || str != NULL)
		return ;
	while (*(lst))
	{
		node = (*(lst))->next;
		free((*(lst))->content);
		(*(lst))->content = NULL;
		free(*(lst));
		*(lst) = node;
	}
}

t_list_g	*gnl_lstlast(t_list_g *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*gnl_strncat(char *dest, const char *src, ssize_t nb, int flag)
{
	char	*r_dest;

	if (dest == NULL)
		return (NULL);
	r_dest = dest;
	if (flag == 1)
		*(dest) = '\0';
	while (*(dest))
		dest++;
	while (*(src) && (nb--) > 0)
		*(dest++) = *(src++);
	*(dest) = '\0';
	return (r_dest);
}
