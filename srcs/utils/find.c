/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:57:22 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 00:59:31 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	map_key_find(void *elem, void *cmp)
{
	t_map	*map;
	char	*cmp_str;

	map = (t_map *)elem;
	cmp_str = (char *)cmp;
	return (!ft_strcmp(map->key, cmp_str));
}

void	map_oldpwd_find(t_envp *env_c, t_node *env_node)
{
	t_map	*map;
	int		flag;

	flag = 0;
	errno = 0;
	while (env_node->next)
	{
		if (map_key_find(env_node->elem, "OLDPWD"))
		{
			flag = 1;
			break ;
		}
		env_node = env_node->next;
	}
	if (!flag)
	{
		map = (t_map *)malloc(sizeof(t_map));
		if (map == NULL)
			exit(errno);
		map->key = ft_strdup("OLDPWD");
		map->val = NULL;
		if (map->key == NULL || dlst_add_last(env_c, (t_map *)map))
			exit(errno);
	}
}

char	*expand_env_find(t_envp *env_c, char *str)
{
	t_map	*map;
	t_node	*node;

	node = env_c->head->next;
	while (node->next)
	{
		map = node->elem;
		if (map_key_find(node->elem, str))
			return (map->val);
		node = node->next;
	}
	return (NULL);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}
