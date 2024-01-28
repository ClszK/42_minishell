/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:02:48 by ljh               #+#    #+#             */
/*   Updated: 2024/01/28 23:07:50 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	copy_env(t_envp *env_c, t_map *export_c)
{
	t_map	*map;
	t_node	*node;
	int		i;

	i = 0;
	errno = 0;
	node = env_c->head->next;
	while (node->next)
	{
		map = node->elem;
		export_c[i].key = ft_strdup(map->key);
		if (map->val)
			export_c[i].val = ft_strdup(map->val);
		else
			export_c[i].val = NULL;
		if (export_c[i].key == NULL || (export_c[i].val == NULL && errno != 0))
			exit(errno);
		i++;
		node = node->next;
	}
}

void	sort_env(t_map *export_c, long lst_size)
{
	int		i;
	int		j;
	t_map	tmp;

	i = -1;
	while (++i < lst_size - 1)
	{
		j = -1;
		while (++j < (lst_size - 1) - i)
		{
			if (ft_strcmp(export_c[j].key, export_c[j + 1].key) > 0)
			{
				tmp = export_c[j];
				export_c[j] = export_c[j + 1];
				export_c[j + 1] = tmp;
			}
		}
	}
}

int	export_print(t_envp *env_c)
{
	t_map	*export_c;
	int		i;

	errno = 0;
	export_c = (t_map *)malloc(sizeof(t_map) * env_c->lst_size);
	if (export_c == NULL)
		exit(errno);
	copy_env(env_c, export_c);
	sort_env(export_c, env_c->lst_size);
	i = -1;
	while (++i < env_c->lst_size)
	{
		if (export_print_sort(export_c, i))
			return (1);
	}
	free_copy(export_c, env_c->lst_size);
	return (0);
}

int	builtin_export(t_parse *parse, t_envp *env_c)
{
	size_t	equal;
	int		i;
	int		export_stat;

	export_stat = 0;
	if (parse->cmd_argv[1] == NULL)
		return (export_print(env_c));
	i = 1;
	while (parse->cmd_argv[i])
	{
		if (check_export_key(parse->cmd_argv[i]))
		{
			print_builtin_error(parse->cmd_argv[0], parse->cmd_argv[i], \
									"not a valid identifier\n");
			export_stat = 1;
		}
		else
		{
			equal = find_char(parse->cmd_argv[i], '=');
			if (check_dup(parse->cmd_argv[i], env_c->head->next, equal))
				append_env(parse->cmd_argv[i], env_c, equal);
		}
		i++;
	}
	return (export_stat);
}
