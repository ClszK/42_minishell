/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 04:22:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/26 18:30:12 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_last_stat(char *start, size_t *size, t_envp *env_c, char *dst)
{
	char	*last_stat_str;

	errno = 0;
	last_stat_str = ft_itoa(env_c->last_stat);
	if (last_stat_str == NULL)
		exit(errno);
	*size += ft_strlen(last_stat_str);
	if (dst)
		ft_strlcat(dst, last_stat_str, *size + 1);
	free(last_stat_str);
	return (start);
}

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

char	*expand_squote(char *start, size_t *size, char *dst)
{
	char	*end;

	end = ft_strchr(start, '\'');
	*size += end - start;
	if (dst)
		ft_strlcat(dst, start, *size + 1);
	return (end);
}

char	*expand_dquote(char *start, size_t *size, t_envp *env_c, char *dst)
{
	char	*end;

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

char	*expand_str_alloc(char *start, t_envp *env_c)
{
	size_t	size;
	int		quote_flag;

	size = 0;
	quote_flag = 0;
	while (*start)
	{
		if (*start == '\'')
		{
			quote_flag = 1;
			start = expand_squote(++start, &size, NULL);
		}
		else if (*start == '"')
		{
			quote_flag = 1;
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
