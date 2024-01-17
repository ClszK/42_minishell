#include "minishell.h"

int	check_unset_key(char *key)
{
	int	i;

	if (ft_isalpha(key[0]) == 0 && key[0] != '_')
		return (1);
	i = 1;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_unset(t_parse *parse, t_envp *env_c)
{
	int	i;

	i = 1;
	errno = 0;
	while (parse->cmd_argv[i])
	{
		if (check_unset_key(parse->cmd_argv[i]))
		{
			if (printf("minishell: unset: `%s': not a valid identifier\n", parse->cmd_argv[i]) < 0)
				return (errno); //echo $? = 1
		}
		else
			dlst_delete(env_c, map_elem_free, map_del_find, parse->cmd_argv[i]);
		i++;
		// builtin_env(env_c);
	}
	return (0);
}