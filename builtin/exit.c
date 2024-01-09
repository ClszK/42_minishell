#include "minishell.h"

int	builtin_exit(t_cmd *parse)
{
	int	flag;
	int	exit_num;

	errno = 0;
	flag = 0;
	if (printf("exit\n") < 0)
		return (errno);
	if (parse->cmd_argv[1] == NULL)
		exit(0);
	exit_num = ft_atol(parse->cmd_argv[1], &flag);
	if (flag == 1)
	{
		if (printf("minishell: exit: %s: numeric argument required\n", parse->cmd_argv[1]) < 0)
			return (errno);
		exit(255);
	}
	if (parse->cmd_argv[2] != NULL)
	{
		if (printf("minishell: exit: too many arguments\n") < 0)
			return (errno);
		return (1);
	}
	exit(exit_num % 256);
}