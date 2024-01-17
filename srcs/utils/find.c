#include "minishell.h"

int	map_del_find(void *elem, void *cmp)
{
	t_map	*map;
	char	*cmp_str;
	int		a;

	map = (t_map *)elem;
	cmp_str = (char *)cmp;
	printf("map key : %s\n", map->key);
	a = !ft_strcmp(map->key, cmp_str);
	printf("strcmp : %d\n", a);
	return (a);
}