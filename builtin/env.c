#include "minishell.h"

int	map_print(void *elem)
{
	t_map	*map;

	map = (t_map *)elem;
	if (map->val)
	{
		if (ft_putstr_fd(map->key, STDOUT_FILENO) || \
			ft_putstr_fd("=", STDOUT_FILENO) || \
			ft_putstr_fd(map->val, STDOUT_FILENO) || \
			ft_putstr_fd("\n", STDOUT_FILENO))
			return (1);
	}
	return (0);
}

int	builtin_env(t_envp *env_c)
{
	if (dlst_print(env_c, map_print))
		return (1);
	return (0);
}
