/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:52:32 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 07:37:44 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_rstring(char const *src, unsigned int n)
{
	char	*r_dest;
	char	*dest;

	if (n == 0)
		return (0);
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	r_dest = dest;
	while (*(src) && n > 0)
	{
		*(dest++) = *(src++);
		n--;
	}
	*(dest) = '\0';
	return (r_dest);
}

int	ft_word_cnt(char const *str, char c)
{
	int		cnt;

	cnt = 0;
	while (*(str))
	{
		if (*(str) != c && *(str))
		{
			cnt++;
			while (*(str) != c && *(str))
				str++;
		}
		else
			str++;
	}
	return (cnt);
}

void	free_split(char	**r_str)
{
	int	i;

	i = 0;
	while (r_str[i])
		free(r_str[i++]);
	free(r_str);
}

int	r_str_fill(char **r_str, char const *s, char c)
{
	unsigned int	each_len;
	unsigned int	i;

	each_len = 0;
	i = 0;
	while (*(s))
	{
		each_len = 0;
		while (*(s + each_len) != c && *(s + each_len))
			each_len++;
		if (each_len != 0)
		{
			r_str[i] = ft_rstring(s, each_len);
			if (r_str[i++] == NULL)
			{
				free_split(r_str);
				return (0);
			}
		}
		if (*(s + each_len) == '\0')
			break ;
		s += each_len + 1;
	}
	r_str[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char				**r_str;

	if (s == NULL)
		return (NULL);
	r_str = (char **)malloc(sizeof(char *) * (ft_word_cnt(s, c) + 1));
	if (r_str == NULL)
		return (NULL);
	if (!r_str_fill(r_str, s, c))
		return (NULL);
	return (r_str);
}
