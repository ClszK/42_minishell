/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 04:22:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/18 10:33:42 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char check_quote_type(char ch)
{
	if (ch == '\'' || ch == '"')
		return (ch);
	return (0);
}

char	expand_valid_quote(char *rline)
{
	while (*rline)
	{
		if (check_quote_type(*rline))
		{
			rline = ft_strchr(rline + 1, *rline);
			if (rline == NULL)
				return (type); // need error process!!
		}
		rline++;
	}
	return (0);
}

void	remove_an_index(char *str)
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

char	*expand_start(char *rline, t_envp *env_c)
{
	while (*rline)
	{
		if (*rline == '\'')
		{
			remove_an_index(rline);
			rline = ft_strchr(rline, '\'');
			remove_an_index(rline);
		}
		else if (*rline == '$')
		{

		}
		else if (*rline == '"')
		{
			if (*rline == '$')
			{

			}
		}
		rline++;
	}
	return (0);
}

char	*expand_size(char *rline, t_envp *env_c)
{
	int	size;

	size = 0;
	while (*rline)
	{
		if (*rline == '\'')
		{
			rline = ft_strchr(rline, '\'');

		}
		else if (*rline == '$')
		{

		}
		else if (*rline == '"')
		{
			if (*rline == '$')
			{

			}
		}
		size++;
		rline++;
	}
	return (0);
}


void	expand_start(t_analyze *alz)
{
	t_node	*parse_node;

	parse_node = alz->head->next;
	while (parse_node->next)
	{

		parse_node = parse_node->next;
	}
}
