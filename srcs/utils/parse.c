/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 04:21:16 by ljh               #+#    #+#             */
/*   Updated: 2024/01/23 05:37:36 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_list(\
			t_cmdline *cmdline, char *rline, int size, enum e_type type)
{
	t_token	*token;

	errno = 0;
	token = token_elem_generate(ft_substr(rline, 0, size), type);
	if (token->str == NULL && errno)
		exit(errno);
	if (dlst_add_last(cmdline, token))
		exit(errno);
}

char	*str_push_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*token_split(char *rline, t_cmdline *cmdline, int i)
{
	enum e_type	type;

	if (is_opertator(rline[i]))
	{
		if (i)
			token_add_list(cmdline, rline, i, WORD);
		rline += i;
		i = 0;
		type = operate_type(rline);
		if (type == APPEND || type == HEREDOC)
			i++;
		token_add_list(cmdline, rline, i + 1, type);
	}
	else if (rline[i])
		token_add_list(cmdline, rline, i, WORD);
	return (str_push_space(rline + i + 1));
}

void	token_cmdline(char *rline, t_cmdline *cmdline)
{
	int		i;
	char	*quote_pos;

	rline = str_push_space(rline);
	while (*rline)
	{
		i = 0;
		while (rline[i] && !(is_opertator(rline[i]) || rline[i] == ' '))
		{
			if (rline[i] == '"' || rline[i] == '\'')
			{
				quote_pos = ft_strchr(rline + i + 1, rline[i]);
				if (quote_pos == NULL)
					i = ft_strlen(rline);
				else
					i = quote_pos - rline;
			}
			i++;
		}
		if (i > 0 && rline[i] == '\0')
			token_add_list(cmdline, rline, i, WORD);
		if (!rline[i])
			return ;
		rline = token_split(rline, cmdline, i);
	}
}
