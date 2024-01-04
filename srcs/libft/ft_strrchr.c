/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:49:23 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/14 18:00:25 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	while (*(s + pos))
		pos++;
	while (pos >= 0)
	{
		if (*(s + pos) == (char)c)
			return ((char *)(s + pos));
		pos--;
	}
	return (NULL);
}
