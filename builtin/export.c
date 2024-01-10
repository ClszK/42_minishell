#include "minishell.h"

int	check_key(char *key)
{
	int	i;

	if (ft_isalpha(key[0]) == 0 && key[0] != '_')
		return (1);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	copy_env(t_envp *env_c, t_map *export_c)
{
	t_map	*map;
	t_node	*node;
	int	i;

	node = env_c->head->next;
	i = 0;
	while (node->next)
	{
		map = node->elem;
		export_c[i].key = ft_strdup(map->key);
		if (map->val)
			export_c[i].val = ft_strdup(map->val);
		else
			export_c[i].val = NULL;
		if (export_c[i].key == NULL \
			|| (export_c[i].val == NULL && errno != 0))
			exit(errno);
		i++;
		node = node->next;
	}
}

void	sort_env(t_envp *env_c, t_map *export_c)
{
	int		i;
	int		j;
	t_map	tmp;

	i = -1;
	while (++i < env_c->lst_size - 1)
	{
		j = -1;
		while (++j < (env_c->lst_size - 1) - i)
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

/* OLDPWD가 없을떄? */
int	export_print(t_envp *env_c)
{
	t_map	*export_c;
	int		i;

	export_c = (t_map *)malloc(sizeof(t_map) * env_c->lst_size);
	if (export_c == NULL)
		exit(errno);
	copy_env(env_c, export_c);
	sort_env(env_c, export_c);
	i = -1;
	while (++i < env_c->lst_size)
	{
		if (ft_strcmp(export_c[i].key, "_") != 0)
		{
			if (export_c[i].val)
				printf("declare -x %s=\"%s\"\n", export_c[i].key, export_c[i].val);
			else
				printf("declare -x %s\n", export_c[i].key);
		}
	}
	// free(export_c); //free하기
	return (0);
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
	return (0);
}

int	builtin_export(t_parse *parse, t_envp *env_c)
{
	t_map	*map;
	int		equal;
	int	i;

	errno = 0;
	if (parse->cmd_argv[1] == NULL)
		return(export_print(env_c));
	i = 1;
	while (parse->cmd_argv[i])
	{
		if (check_key(parse->cmd_argv[i]))
		{
			if (printf("minishell: export: `%s': not a valid identifier\n", parse->cmd_argv[i]) < 0)
				return (errno); //echo $? = 1
		}
		else
		{
			map = (t_map*)malloc(sizeof(t_map));
			if (map == NULL)
				exit(errno);
			equal = find_char(parse->cmd_argv[i], '=');
			printf("\n%d\n", equal);
			if (equal)
			{
				map->key = ft_substr(parse->cmd_argv[i], 0, equal);
				map->val = ft_strdup(parse->cmd_argv[i] + equal + 1);
			}
			else
			{
				map->key = ft_strdup(parse->cmd_argv[i]);
				map->val = NULL;
			}
			if (map->key == NULL || (map->val == NULL && errno != 0) \
				|| dlst_add_last(env_c, (t_map*)map))
				exit(errno);
			builtin_env(env_c);
		}
		i++;
	}
	return (0);
}
