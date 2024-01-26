/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:43:08 by ljh               #+#    #+#             */
/*   Updated: 2024/01/26 21:53:22 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	앞에서 구한 크기를 토대로 ft_strlcat 함수를 통해 붙여넣기 하는 함수이다.
	작은 따옴표는 확장 x,
	큰 따옴표는 확장 o
	echo $PWD같은 경우는 따옴표로 둘러 쌓여있지 않더라도 확장 진행한다.
*/
char	*expand_str_cpy(char *start, char *dst, t_envp *env_c)
{
	size_t	size;

	size = 0;
	while (*start)
	{
		if (*start == '\'' || *start == '"')
		{
			if (*start == '\'')
				start = expand_squote(start, &size, dst);
			else
				start = expand_dquote(start, &size, env_c, dst);
			arr_one_left_shift(start);
		}
		else
		{
			if (can_dollar_expand(start))
				start = expand_dollar(++start, &size, env_c, dst);
			else if (!(*start == '$' && check_quote_type(*(start + 1))))
				dst[size++] = *start;
			start++;
		}
	}
	return (dst);
}

/*
	cmd_argv 안에 담긴 각각의 값을 확장하는데,
	cmd_argv에 ls, $PWD가 있으면
	ls는 그대로 다시 cmd_argv에 담기고
	$PWD는 확장한 값을 담는다.
*/
void	expand_cmd_argv(char **cmd_argv, t_envp *env_c)
{
	char	*expand_str;
	int		i;

	i = 0;
	errno = 0;
	while (cmd_argv[i])
	{
		expand_str = expand_str_alloc(cmd_argv[i], env_c);
		if (errno)
			exit(errno);
		if (expand_str == NULL)
		{
			free(cmd_argv[i]);
			split_shift(cmd_argv, i);
			continue ;
		}
		expand_str_cpy(cmd_argv[i], expand_str, env_c);
		free(cmd_argv[i]);
		cmd_argv[i] = expand_str;
		i++;
	}
}

void	expand_stdio(t_stdio *std, t_envp *env_c)
{
	t_node	*stdio_node;
	t_token	*token;
	char	*expand_str;

	stdio_node = std->head->next;
	while (stdio_node->elem)
	{
		token = stdio_node->elem;
		expand_str = expand_str_alloc(token->str, env_c);
		if (errno)
			exit(errno);
		if (expand_str == NULL)
		{
			errno = 0;
			token->env_val = ft_strdup(token->str);
			if (token->env_val == NULL && errno)
				exit(errno);
		}
		else
			expand_str_cpy(token->str, expand_str, env_c);
		free(token->str);
		token->str = expand_str;
		stdio_node = stdio_node->next;
	}
}

/*
	t_analyze 연결리스트에 담긴 각각의 노드안에 
	cmd_argv, here_doc_lst, std_lst가 있을텐데
	이 안에 환경변수 확장과 따옴표 제거 작업을 진행한다.
*/
void	expand_start(t_analyze *alz, t_envp *env_c)
{
	t_node	*parse_node;
	t_parse	*parse;

	parse_node = alz->head->next;
	while (parse_node->elem)
	{
		parse = parse_node->elem;
		expand_cmd_argv(parse->cmd_argv, env_c);
		expand_stdio(parse->here_doc_lst, env_c);
		expand_stdio(parse->std_lst, env_c);
		parse_node = parse_node->next;
	}
}
