#include "minishell.h"

int	map_del_find(void *elem, void *cmp)
{
	t_map	*map;
	char	*cmp_str;

	map = (t_map *)elem;
	cmp_str = (char *)cmp;
	return (!ft_strcmp(map->key, cmp_str));
}