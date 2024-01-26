/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 04:21:16 by ljh               #+#    #+#             */
/*   Updated: 2024/01/26 18:45:36 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	str, type을 가진 노드를 cmdline 연결리스트에 추가.
	여기서 str은 ls -al | cat이라 하면 
	ls, -al, |, cat을 의미.
	type은
	WORD, WORD, PIPE, WORD 형태로 삽입됨.
*/
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

/*
	연산자인지 체크.
	연산자라면 해당 연산자에 맞는 TYPE을 가지고 t_cmdline 연결리스트 마지막 노드에 삽입.
	단어라면 TYPE을 WORD라 지정하고 연결리스트 마지막 노드 삽입.
*/
char	*token_split(char *rline, t_cmdline *cmdline, int i)
{
	enum e_type	type;

	if (is_operator(rline[i]))
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

/*
	readline 함수에서 받아온 문자열을 token 단위로 파싱.
	token 단위의 구분자는 연산자, 단어.
	먼저, 화이트스페이스를 밀고 난 후, token으로 분리.
*/
void	token_cmdline(char *rline, t_cmdline *cmdline)
{
	int		i;
	char	*quote_pos;

	rline = str_push_space(rline);
	while (*rline)
	{
		i = -1;
		while (rline[++i] && !(is_operator(rline[i]) \
			|| ((rline[i] >= 9 && rline[i] <= 13) || rline[i] == 32)))
		{
			if (rline[i] == '"' || rline[i] == '\'')
			{
				quote_pos = ft_strchr(rline + i + 1, rline[i]);
				if (quote_pos == NULL)
					i = ft_strlen(rline);
				else
					i = quote_pos - rline;
			}
		}
		if (i > 0 && rline[i] == '\0')
			token_add_list(cmdline, rline, i, WORD);
		if (!rline[i])
			return ;
		rline = token_split(rline, cmdline, i);
	}
}
