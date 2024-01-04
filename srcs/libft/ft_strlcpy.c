/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:23:31 by jeholee           #+#    #+#             */
/*   Updated: 2023/11/22 01:43:32 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (*(src) && (dstsize--) > 1)
		*(dst++) = *(src++);
	*(dst) = '\0';
	return (len);
}
