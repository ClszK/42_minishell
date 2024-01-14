/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 04:21:16 by ljh               #+#    #+#             */
/*   Updated: 2024/01/14 00:27:56 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_list(\
			t_cmdline *cmdline, char *rline, int size, enum e_type type)
{
	t_token	*token;

	errno = 0;
	token = token_elem_generate();
	token->str = ft_substr(rline, 0, size);
	if (token->str == NULL && errno)
		exit(errno);
	token->type = type;
	if (dlst_add_last(cmdline, token))
		exit(errno);
}

char	*str_push_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

int	is_opertator(char ch)
{
	if (ch == '<' || ch == '>' || ch == '|')
		return (1);
	return (0);
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
		if (rline[i] == '|')
			type = PIPE;
		else
			type = REDIRECT;
		if ((rline[i] == '<' && rline[i + 1] == '<') || \
			(rline[i] == '>' && rline[i + 1] == '>'))
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
		if (rline[i] == '\0')
			token_add_list(cmdline, rline, i, WORD);
		rline = token_split(rline, cmdline, i);
	}
}
