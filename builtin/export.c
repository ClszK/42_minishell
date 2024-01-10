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

int	builtin_export(t_parse *parse, t_envp *env_c)
{
	int	i;

	errno = 0;
	if (parse->cmd_argv[1] == NULL)
		//print export
	i = 1;
	while (parse->cmd_argv[i])
	{
		if (check_key(parse->cmd_argv[i]))
		{
			if (printf("minishell: export: `%s': not a valid identifier\n", parse->cmd_argv[i]) < 0)
				return (errno);
		}
		i++;
	}
}