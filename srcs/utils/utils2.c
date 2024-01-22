/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:42:59 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/22 17:00:27 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_quote_type(char ch)
{
	if (ch == '\'' || ch == '"')
		return (ch);
	return (0);
}

int	is_dollar_sperator(char ch)
{
	if (is_opertator(ch) || ch == ' ' || ch == '\0' || check_quote_type(ch) \
		|| ch == '$')
		return (1);
	return (0);
}

int	can_dollar_expand(char *str)
{
	if (*str == '$' && !is_dollar_sperator(*(str + 1)))
		return (1);
	return (0);
}

void	arr_one_left_shift(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

/* need error process!! */
char	valid_quote(char *rline)
{
	char	type;

	while (*rline)
	{
		type = check_quote_type(*rline);
		if (type)
		{
			rline = ft_strchr(rline + 1, *rline);
			if (rline == NULL)
				return (type);
		}
		rline++;
	}
	return (0);
}
