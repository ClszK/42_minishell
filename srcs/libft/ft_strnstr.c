/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:03:01 by jeholee           #+#    #+#             */
/*   Updated: 2023/11/15 18:42:01 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;

	n_len = ft_strlen(needle);
	if (*(needle) == '\0')
		return ((char *)haystack);
	while (len > 0 && *(haystack))
	{
		if (*(haystack) == *(needle) && len >= n_len
			&& ft_strncmp(haystack, needle, n_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
