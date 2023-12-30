/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:35:55 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/15 22:42:18 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t			ft_strlen(const char *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r_s;
	unsigned int	len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	r_s = (char *)malloc(sizeof(char) * (len + 1));
	if (r_s == NULL)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		r_s[i] = f(i, *(s + i));
		i++;
	}
	r_s[i] = '\0';
	return (r_s);
}
