#include "minishell.h"

int	check_dup(char	*cmd_argv, t_envp *env_c, size_t equal)
{
	t_map	*cmp;
	t_node	*node;
	char	*argv_key;

	errno = 0;
	argv_key = ft_substr(cmd_argv, 0, equal);
	if (argv_key == NULL)
		exit(errno);
	node = env_c->head->next;
	while (node->next)
	{
		cmp = node->elem;
		if (cmp != NULL && !ft_strcmp(argv_key, cmp->key))
		{
			if (equal != ft_strlen(cmd_argv))
			{
				if (cmp->val)
					free(cmp->val);
				update_env(cmd_argv, cmp, equal);
				free(argv_key);
			}
			return (0);
		}
		node = node->next;
	}
	free(argv_key);
	return (1);
}

void	update_env(char *cmd_argv, t_map *cur, size_t equal)
{
	errno = 0;
	cur->val = ft_strdup(cmd_argv + equal + 1);
	if (cur->val == NULL)
		exit(errno);
}

void	append_env(char *cmd_argv, t_envp *env_c, size_t equal)
{
	t_map	*map;

	errno = 0;
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		exit(1);
	map->key = ft_substr(cmd_argv, 0, equal);
	if (equal != ft_strlen(cmd_argv))
		map->val = ft_strdup(cmd_argv + equal + 1);
	else
		map->val = NULL;
	if (map->key == NULL || (map->val == NULL && errno != 0) \
		|| dlst_add_last(env_c, (t_map *)map))
		exit(1);
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

int	export_print_sort(t_map *export_c, int pos)
{
	if (ft_strcmp(export_c[pos].key, "_") != 0)
	{
		if (export_c[pos].val)
		{
			if (ft_putstr_fd("declare -x ", STDOUT_FILENO) || \
				ft_putstr_fd(export_c[pos].key, STDOUT_FILENO) || \
				ft_putstr_fd("=\"", STDOUT_FILENO) || \
				ft_putstr_fd(export_c[pos].val, STDOUT_FILENO) || \
				ft_putstr_fd("\"\n", STDOUT_FILENO))
				return (1);
		}
		else if (ft_putstr_fd("declare -x ", STDOUT_FILENO) || \
				ft_putstr_fd(export_c[pos].key, STDOUT_FILENO) || \
				ft_putstr_fd("\n", STDOUT_FILENO))
			return (1);
	}
	return (0);
}
