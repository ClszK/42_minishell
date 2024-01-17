#include "minishell.h"

int	check_export_key(char *key)
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
	int		i;

	node = env_c->head->next;
	i = 0;
	errno = 0;
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

void	free_copy(t_map *export_c, long lst_size)
{
	long	i;

	i = 0;
	while (i < lst_size)
	{
		free(export_c[i].key);
		free(export_c[i].val);
		i++;
	}
	free(export_c);
}

int	export_print(t_envp *env_c)
{
	t_map	*export_c;
	int		i;

	export_c = (t_map *)malloc(sizeof(t_map) * env_c->lst_size);
	if (export_c == NULL)
		exit(errno);
	copy_env(env_c, export_c);
	sort_env(export_c, env_c->lst_size);
	i = -1;
	while (++i < env_c->lst_size)
	{
		if (ft_strcmp(export_c[i].key, "_") != 0)
		{
			if (export_c[i].val)
			{
				if (ft_putstr_fd("declare -x ", STDOUT_FILENO) || \
					ft_putstr_fd(export_c[i].key, STDOUT_FILENO) || \
					ft_putstr_fd("=", STDOUT_FILENO) || \
					ft_putstr_fd(export_c[i].val, STDOUT_FILENO) || \
					ft_putstr_fd("\n", STDOUT_FILENO))
					return (errno);
			}
			else if (ft_putstr_fd("declare -x ", STDOUT_FILENO) || \
					ft_putstr_fd(export_c[i].key, STDOUT_FILENO) || \
					ft_putstr_fd("\n", STDOUT_FILENO))
					return (errno);
		}
	}
	free_copy(export_c, env_c->lst_size);
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
	return (i);
}

void	update_env(char *cmd_argv, t_map *cur, size_t equal)
{
	errno = 0;
	cur->val = ft_strdup(cmd_argv + equal + 1);
	if (cur->val == NULL)
		exit(errno);
}

/*경우의수 생각하기*/
int	check_dup(char	*cmd_argv, t_envp *env_c, size_t equal)
{
	t_map	*cmp;
	t_node	*node;

	node = env_c->head->next;
	while (node->next)
	{
		cmp = node->elem;
		if (cmp != NULL && !ft_strncmp(cmd_argv, cmp->key, ft_strlen(cmp->key)))
		{
			if (equal != 0) // =이 있을 때 val 생성
			{
				if (cmp->val)
					free(cmp->val);
				update_env(cmd_argv, cmp, equal); //기존 val free 후 새롭게 val 만들기
			}
			return (0);
		}
		node = node->next;
	}
	return (1);
}

void	append_env(char *cmd_argv, t_envp *env_c, size_t equal)
{
	t_map	*map;

	errno = 0;
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		exit(errno);
	map->key = ft_substr(cmd_argv, 0, equal);
	if (equal != ft_strlen(cmd_argv))
		map->val = ft_strdup(cmd_argv + equal + 1);
	else
		map->val = NULL;
	if (map->key == NULL || (map->val == NULL && errno != 0) \
		|| dlst_add_last(env_c, (t_map *)map))
		exit(errno);
}

int	builtin_export(t_parse *parse, t_envp *env_c)
{
	size_t	equal;
	int		i;
	int		export_stat;

	errno = 0;
	export_stat = 0;
	if (parse->cmd_argv[1] == NULL)
		return (export_print(env_c));
	i = 1;
	while (parse->cmd_argv[i])
	{
		if (check_export_key(parse->cmd_argv[i]))
		{
			if (print_builtin_error(parse->cmd_argv[0], parse->cmd_argv[i], \
									"not a valid identifier\n"))
				return (errno); //echo $? = 1
			export_stat = 1;
		}
		else
		{
			equal = find_char(parse->cmd_argv[i], '=');
			if (check_dup(parse->cmd_argv[i], env_c, equal))
				append_env(parse->cmd_argv[i], env_c, equal);
			builtin_env(env_c);
		}
		i++;
	}
	return (export_stat);
}
