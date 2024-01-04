/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:11:33 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 01:09:56 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	// 에러 제거

char	*get_next_line(int fd)
{
	static t_list_g	*tmp[OPEN_MAX + 1];
	char			*rline;
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			rsize;

	rline = NULL;
	if (fd >= OPEN_MAX || fd < 0 || BUFFER_SIZE == 0 || OPEN_MAX == 0)
		return (NULL);
	rsize = 1;
	while (1)
	{
		if (rsize == 0 || (tmp[fd] != NULL \
		&& (gnl_lstlast(tmp[fd]))->lnpos != -1))
		{
			rline = gnl_lstcat(&tmp[fd]);
			gnl_lstclear(&tmp[fd], rline);
			break ;
		}
		rsize = read(fd, buffer, BUFFER_SIZE);
		if (read_line(&tmp[fd], buffer, rsize) < 0)
			break ;
	}
	return (rline);
}

int	read_line(t_list_g **tmp, char *buffer, ssize_t readsize)
{
	if (readsize < 0)
	{
		gnl_lstclear(tmp, NULL);
		return (-1);
	}
	if (readsize == 0)
		return (1);
	buffer[readsize] = '\0';
	if (gnl_lstadd_back(tmp, gnl_lstnew(buffer)) == -1)
	{
		gnl_lstclear(tmp, NULL);
		return (-1);
	}
	return (1);
}

char	*gnl_lstcat(t_list_g **tmp)
{
	char		*str;
	t_list_g	*node;
	size_t		nlen;

	if (*tmp == NULL)
		return (NULL);
	node = gnl_lstlast(*tmp);
	nlen = node->totallen;
	if (node->lnpos != -1)
		nlen = nlen - node->len + node->lnpos;
	str = (char *)malloc(sizeof(char) * (nlen + 1));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	node = (*tmp);
	while (node->next != NULL)
	{
		(void)gnl_strncat(str, node->content, node->len, 0);
		node = node->next;
	}
	str = gnl_lstcat_2(tmp, node, str);
	return (str);
}

char	*gnl_lstcat_2(t_list_g **tmp, t_list_g *node, char *str)
{
	size_t	nlen;
	char	*stmp;

	if (node->lnpos != -1 && node->content[node->lnpos] != '\0')
	{
		nlen = node->len - node->lnpos + 1;
		(void)gnl_strncat(str, node->content, node->lnpos, 0);
		stmp = gnl_strncat(malloc(nlen), node->content + node->lnpos, nlen, 1);
		gnl_lstclear(tmp, NULL);
		if (stmp == NULL || gnl_lstadd_back(tmp, gnl_lstnew(stmp)) == -1)
		{
			free(str);
			str = NULL;
		}
		free(stmp);
	}
	else
	{
		(void)gnl_strncat(str, node->content, node->len, 0);
		gnl_lstclear(tmp, NULL);
	}
	return (str);
}
