/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:09 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/14 18:25:50 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	pos;

	pos = 0;
	while (n > pos)
	{
		if (*((unsigned char *)s + pos) == (unsigned char)c)
			return ((unsigned char *)s + pos);
		(++pos);
	}
	return (NULL);
}
