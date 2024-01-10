#include "minishell.h"

int	map_print(void *elem)
{
	t_map	*map;

	map = (t_map *)elem;
	errno = 0;
	if (map->val)
		if (printf("%s=%s\n", map->key, map->val) < 0)
			return (errno);
	return (0);
}

int	builtin_env(t_envp *env_c)
{
	if (dlst_print(env_c, map_print))
		return (errno);
	return (0);
}