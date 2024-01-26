/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:42:59 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/26 20:08:47 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_type(char ch)
{
	if (ch == '\'')
		return (SQUOTE_ERROR);
	if (ch == '"')
		return (DQUOTE_ERROR);
	return (0);
}

/*
	여기서 구분자는 연산자, \0, 따옴표, $, /, 화이트스페이스로 지정했다.
	원래라면 더 다양한 구분자가 존재하지만, minishell에서 구현해야하는 부분만 구분자로 지정하기로
	했다.
*/
int	is_dollar_sperator(char ch)
{
	if (is_operator(ch) || ch == '\0' || check_quote_type(ch) \
		|| ch == '$' || ch == '/' || (ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

/*
	확장이 가능한 $인지 체크한다.
	$만 단독으로 오면 그냥 $를 출력한다.
	$바로 뒤가 $구분자가 오면 $는 출력해야될 문자로 판단.
*/
int	can_dollar_expand(char *str)
{
	if (*str == '$' && !is_dollar_sperator(*(str + 1)))
		return (1);
	return (0);
}

/*
	현재 위치로 오른쪽 값을 땡긴다.
	"hello"면
	heelo"가 된다.
*/
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

/* 	
	인용 처리 함수
	여기서 인용 처리 함수란, 따옴표로 잘 감싸져있는지 체크
	타당하지 않으면 해당 에러 Type 반환.
*/
int	valid_quote(char *rline)
{
	int	type;

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
