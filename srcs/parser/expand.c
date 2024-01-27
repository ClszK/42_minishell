/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 04:22:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/28 01:13:56 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	$? 예외처리 함수.
*/
char	*expand_last_stat(char *start, size_t *size, t_envp *env_c, char *dst)
{
	char	*last_stat_str;

	errno = 0;
	if (g_signo)
	{
		if (g_signo == 1)
			env_c->last_stat = 1;
		else if (g_signo == 2)
			env_c->last_stat = 130;
		else if (g_signo == 3)
			env_c->last_stat = 131;
		g_signo = 0;
	}
	last_stat_str = ft_itoa(env_c->last_stat);
	if (last_stat_str == NULL)
		exit(errno);
	*size += ft_strlen(last_stat_str);
	if (dst)
		ft_strlcat(dst, last_stat_str, *size + 1);
	free(last_stat_str);
	return (start);
}

/*
	확장 가능한 $이므로 확장을 진행한다.
	여기서 $?형태는 이전 명령어의 종료코드를 나타내므로 예외처리를 해줬다.
	이후로 env_c안에서 확장 가능한 key값을 찾아 순회해서 찾는 과정.
*/
char	*expand_dollar(char *start, size_t *size, t_envp *env_c, char *dst)
{
	char	*end;
	char	*env_val;
	char	*str_dup;

	errno = 0;
	end = start;
	if (*start == '?')
		return (expand_last_stat(start, size, env_c, dst));
	while (*end && !is_dollar_sperator(*end))
		end++;
	str_dup = ft_substr(start, 0, end - start);
	if (str_dup == NULL && errno)
		exit(errno);
	env_val = expand_env_find(env_c, str_dup);
	free(str_dup);
	if (env_val)
	{
		*size += ft_strlen(env_val);
		if (dst)
			ft_strlcat(dst, env_val, *size + 1);
	}
	return (end - 1);
}

/*
	작은 따옴표는 확장할 필요가 없기 때문에
	작은 따옴표를 제외한 크기를 구한다.
*/
char	*expand_squote(char *start, size_t *size, char *dst)
{
	char	*end;

	if (dst)
		arr_one_left_shift(start);
	end = ft_strchr(start, '\'');
	*size += end - start;
	if (dst)
		ft_strlcat(dst, start, *size + 1);
	return (end);
}

/*
	큰 따옴표는 내부에 확장할 $가 있으면 확장을 진행해주어야한다.
	이를 처리하는 함수.
*/
char	*expand_dquote(char *start, size_t *size, t_envp *env_c, char *dst)
{
	char	*end;

	if (dst)
		arr_one_left_shift(start);
	end = ft_strchr(start, '"');
	while (start != end)
	{
		if (can_dollar_expand(start))
			start = expand_dollar(++start, size, env_c, dst);
		else
		{
			*size += 1;
			if (dst)
				ft_strlcat(dst, start, *size + 1);
		}
		start++;
	}
	return (end);
}

/*
	여기는 확장되기 전의 str을 가지고 확장될 str의 크기를 구하는 함수.
	$PWD면 길이가 4인데 확장되면 
	예를 들어, /Users/ljh/Documents/42_minishell형태가 된다.
	그래서 크기를 구한다음 동적 할당하는 작업 진행.
	여기서 hi"$PWD" 형태일 경우
	hi/Users/ljh/Documents/42_minishell이므로
	이를 체크하는 로직을 가지고 있다.
*/
char	*expand_str_alloc(char *start, t_envp *env_c)
{
	size_t	size;
	int		quote_flag;

	size = 0;
	quote_flag = 0;
	while (*start)
	{
		if (check_quote_type(*start))
		{
			quote_flag = 1;
			if (*start == '\'')
				start = expand_squote(++start, &size, NULL);
			else if (*start == '"')
				start = expand_dquote(++start, &size, env_c, NULL);
		}
		else if (can_dollar_expand(start))
			start = expand_dollar(++start, &size, env_c, NULL);
		else
			size++;
		start++;
	}
	errno = 0;
	if (quote_flag == 0 && size == 0)
		return (NULL);
	return (ft_calloc(sizeof(char), size + 1));
}
