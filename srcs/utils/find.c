#include "minishell.h"

int	map_key_find(void *elem, void *cmp)
{
	t_map	*map;
	char	*cmp_str;

	map = (t_map *)elem;
	cmp_str = (char *)cmp;
	return (!ft_strcmp(map->key, cmp_str));
}

void	map_oldpwd_find(t_envp *env_c)
{
	t_map	*map;
	t_node	*node;
	int		flag;

	flag = 0;
	node = env_c->head->next;
	while (node->next)
	{
		if (map_key_find(node->elem, "OLDPWD"))
		{
			flag = 1;
			break ;
		}
		node = node->next;
	}
	if (!flag)
	{
		map = (t_map *)malloc(sizeof(t_map));
		if (map == NULL)
			exit(errno);
		map->key = ft_strdup("OLDPWD");
		map->val = NULL;
		if (map->key == NULL || dlst_add_last(env_c, (t_map*)map))
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
