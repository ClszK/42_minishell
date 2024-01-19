/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 04:22:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/19 09:56:46 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	expand_valid_quote(char *rline);
char	*expand_dollar_end_pos(char *start);
char	*expand_squote(char *start, size_t *size);
char	*expand_dquote(char *start, size_t *size, t_envp *env_c, char *dst);
char	*expand_dollar(char *start, size_t *size, t_envp *env_c, char *dst);
char	*expand_str_alloc(char *start, t_envp *env_c);
// char	*expand_strcpy(char *src, char *dst, t_envp *env_c, size_t *size);
void	expand_start(t_analyze *alz, t_envp *env_c);

char	expand_valid_quote(char *rline)
{
	char	type;

	while (*rline)
	{
		type = check_quote_type(*rline);
		if (type)
		{
			rline = ft_strchr(rline + 1, *rline);
			if (rline == NULL)
				return (type); // need error process!!
		}
		rline++;
	}
	return (0);
}

char	*expand_dollar_end_pos(char *start)
{
	char	*end;

	end = start;
	while (*end && !is_dollar_sperator(*end))
		end++;
	return (end - 1);
}

// char	*expand_squote(char *start)
// {
// 	char	*end;

// 	arr_one_left_shift(start);
// 	end = ft_strchr(start, '\'');
// 	arr_one_left_shift(end);
// 	return (end);
// }

// char	*expand_dquote(char *start, size_t *size, t_envp *env_c)
// {
// 	char	*end;
// 	char	*env_val;
// 	char	*dollar_end_pos;
// 	char	*rstr;
// 	char	*rstr_tmp;

// 	end = ft_strchr(start, '"');
// 	rstr = NULL;
// 	while (start != end)
// 	{
// 		if (can_dollar_expand(start))
// 		{
// 			dollar_end_pos = expand_dollar_end_pos(start + 1);
// 			env_val = expand_env_find(env_c, start + 1, dollar_end_pos - start - 1);
// 			if (env_val)
// 			{
// 				*start = '\0';
// 				if (rstr)
// 				{
// 					rstr_tmp = rstr;
// 					rstr = ft_strjoin(rstr, env_val);
// 					free(rstr_tmp);
// 				}
// 				else
// 					rstr = ft_strjoin(rstr, env_val);
// 			}
// 			start = dollar_end_pos;
// 		}
// 		start++;
// 	}
// 	arr_one_left_shift(end);
// 	return (rstr);
// }

// char	*expand_dollar_ptr(char *start, size_t *size, t_envp *env_c)
// {
// 	char	*end;
// 	char	*env_val;

// 	end = expand_dollar_end_pos(start);
// 	env_val = expand_env_find(env_c, start, end - start);
// 	if (env_val)
// 		*size += ft_strlen(env_val);
// 	return (end);
// }

// char	*expand_str_alloc(char *start, t_envp *env_c)
// {
// 	size_t	size;
// 	char	*quote_end_pos;
// 	char	*rstr;
 
// 	size = 0;
// 	while (*start)
// 	{
// 		if (*start == '\'')
// 			start = expand_squote(start, &size);
// 		else if (*start == '"')
// 		{
// 			arr_one_left_shift(start);
// 			quote_end_pos = ft_strchr(start, '"');
// 			start = expand_dquote(start, &size, env_c, NULL);
// 		}
// 		else if (can_dollar_expand(start))
// 		{
// 			expand_dollar_ptr(++start, &size, env_c);
// 			start = expand_dollar_end_pos(start);
// 		}
// 		else
// 			size++;
// 	}
// 	errno = 0;
// 	rstr = malloc(sizeof(char) * (size + 1));
// 	if (rstr == NULL)
// 		exit(errno);
// 	return (rstr);
// }

// char	*expand_strcpy(char *src, char *dst, t_envp *env_c)
// {
// 	size_t	size;
// 	char	*start;
// 	char	*end;
 
// 	size = 0;
// 	while (*start)
// 	{
// 		if (*start == '\'')
// 		{
// 			end = expand_squote(++start, &size);
// 		}
// 		else if (*start == '"')
// 			start = expand_dquote(++start, &size, env_c, dst);
// 		else if (can_dollar_expand(start))
// 		{
// 			// ft_strlcat(dst, )
// 			start = expand_dollar_ptr(++start, &size, env_c);
// 		}
// 		else
// 			*start = *src;
// 		start++;
// 	}
// }

void	expand_start(t_analyze *alz, t_envp *env_c)
{
	t_node	*parse_node;

	parse_node = alz->head->next;
	while (parse_node->next)
	{

		parse_node = parse_node->next;
	}
}

char	*expand_dollar(char *start, size_t *size, t_envp *env_c, char *dst)
{
	char	*end;
	char	*env_val;
	char	*str_dup;

	errno = 0;
	end = expand_dollar_end_pos(start);
	str_dup = ft_substr(start, 0, end - start + 1);
	if (str_dup == NULL && errno)
		exit(errno);
	env_val = expand_env_find(env_c, str_dup);
	free(str_dup);
	if (env_val)
		*size += ft_strlen(env_val);
	if (dst)
		ft_strlcat(dst, env_val, *size);
	return (end);
}

char	*expand_squote(char *start, size_t *size)
{
	char	*end;

	end = ft_strchr(start, '\'');
	*size += end - start - 1;
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
				ft_strlcat(dst, start, *size);
		}
		start++;
	}
	return (end);
}

char	*expand_str_alloc(char *start, t_envp *env_c)
{
	size_t	size;
	char	*rstr;
 
	size = 0;
	while (*start)
	{
		if (*start == '\'')
			start = expand_squote(++start, &size);
		else if (*start == '"')
			start = expand_dquote(++start, &size, env_c, NULL);
		else if (can_dollar_expand(start))
			start = expand_dollar(++start, &size, env_c, NULL);
		else
			size++;
		start++;
	}
	errno = 0;
	printf("malloc size: %zu\n", size);
	rstr = ft_calloc(sizeof(char), size + 1);
	if (rstr == NULL)
		exit(errno);
	return (rstr);
}

char	*expand_str_cpy(char *src, char *dst, t_envp *env_c)
{
	size_t	size;
	char	*start;
	char	*end;
 
	size = 0;
	start = src;
	while (*start)
	{
		if (check_quote_type(*start))
		{
			arr_one_left_shift(start);
			if (*start == '\'')
				start = expand_squote(start, &size);
			else
				start = expand_dquote(start, &size, env_c, dst);
			arr_one_left_shift(start);
		}
		else
		{
			if (can_dollar_expand(start))
				start = expand_dollar(++start, &size, env_c, dst);
			else
				dst[size++] = *start;
			start++;
		}
	}
	return (dst);
}