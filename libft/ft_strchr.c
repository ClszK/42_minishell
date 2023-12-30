/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:11 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/14 17:47:28 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	while (*(s))
	{
		if (*(s) == (char)c)
			return ((char *)s);
		s++;
	}
	if (*(s) == (char)c)
		return ((char *)s);
	return (NULL);
}
