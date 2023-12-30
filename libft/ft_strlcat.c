/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:05:30 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/17 01:59:39 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	dst_cat_len;

	dst_cat_len = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	while (*(dst) && dstsize > dst_cat_len + 1)
	{
		dst_cat_len++;
		dst++;
	}
	while (*(src) && dstsize > dst_cat_len + 1)
	{	
		*(dst++) = *(src++);
		dst_cat_len++;
	}
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	*(dst) = '\0';
	return (src_len + dst_len);
}
