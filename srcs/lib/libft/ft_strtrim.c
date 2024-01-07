/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:29:03 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/16 22:49:26 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);

void	ascii_fill(char *ascii, char const *set)
{
	int	i;

	i = 0;
	while (i < 256)
		ascii[i++] = 0;
	while (*(set))
		ascii[(int)*(set++) + 128] = 1;
}

void	s1_plus_and_cnt(char const **s, int *cnt, char *ascii)
{
	int			i;
	char const	*s1;

	i = 0;
	s1 = *(s);
	while (*(s1))
	{
		if (ascii[(int)*(s1) + 128] == 0)
			break ;
		s1++;
	}
	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (ascii[(int)s1[i--] + 128] == 0)
			break ;
		*(cnt) += 1;
	}
	*(s) = s1;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	ascii[256];
	char	*str;
	int		i;
	int		cnt;

	cnt = 0;
	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	ascii_fill(ascii, set);
	s1_plus_and_cnt(&s1, &cnt, ascii);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) - cnt + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + cnt))
		str[i++] = *(s1++);
	str[i] = '\0';
	return (str);
}
