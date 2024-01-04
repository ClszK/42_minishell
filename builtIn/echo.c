#include "../minishell.h"

int	builtin_echo(t_parse *parse)
{
	int	i;
	int	j;
	int	n_flag;

	i = 0;
	j = -1;
	n_flag = 0;
	while (parse->cmd_argv[++i])
	{
		if (parse->cmd_argv[i][0] == '-')
		{
			while (parse->cmd_argv[i][++j] == 'n')
			{
				
			}
		}
	}
}