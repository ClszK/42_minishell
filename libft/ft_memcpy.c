/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:01:46 by jeholee           #+#    #+#             */
/*   Updated: 2023/07/05 23:28:54 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*r_dst;

	r_dst = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while ((n--) > 0)
		*((unsigned char *)dst++) = *((unsigned char *)src++);
	return (r_dst);
}
