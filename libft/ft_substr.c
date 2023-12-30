/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:16:31 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/21 16:57:25 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);

char	*nullstr(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	sublen;
	unsigned int	pos;

	sublen = start;
	pos = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (nullstr());
	while (s[sublen] && (len--) > 0)
		sublen++;
	sublen -= start;
	substr = (char *)malloc(sizeof(char) * (sublen + 1));
	if (substr == NULL)
		return (NULL);
	while ((sublen--) > 0)
	{
		substr[pos] = s[pos + start];
		pos++;
	}
	substr[pos] = '\0';
	return (substr);
}
