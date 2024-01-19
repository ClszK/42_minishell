/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:42:59 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/19 10:23:56 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_move_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

long	ft_atol(char *str, int *flag)
{
	int		i;
	int		sign;
	long	result;
	long	tmp;

	sign = 1;
	result = 0;
	i = ps_move_sign(str, &sign);
	if (!str[i--])
		*flag = 1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			*flag = 1;
		tmp = result;
		result = (result * 10) + (str[i] - '0');
	}
	if (tmp > result)
		*flag = 1;
	if (sign == -1)
		if (result < 0)
			*flag = 1;
	result *= sign;
	return (result);
}

enum e_type	operate_type(char *str)
{
	if (*str == '|')
		return (PIPE);
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (APPEND);
		return (OUTPUT);
	}
	else
		return (NONE);
}

int	is_redirect(t_token *token)
{
	if (token->type == NONE || token->type == WORD || token->type == PIPE)
		return (0);
	return (1);
}

int	is_opertator(char ch)
{
	if (ch == '<' || ch == '>' || ch == '|')
		return (1);
	return (0);
}

char	check_quote_type(char ch)
{
	if (ch == '\'' || ch == '"')
		return (ch);
	return (0);
}

int	is_dollar_sperator(char ch)
{
	if (is_opertator(ch) || ch == ' ' || ch == '\0' || check_quote_type(ch))
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
