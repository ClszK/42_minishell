#include "minishell.h"

int	builtin_exit(t_parse *parse)
{
	int	flag;
	int	exit_num;

	errno = 0;
	flag = 0;
	if (ft_putstr_fd("exit", STDOUT_FILENO) || \
		ft_putstr_fd("\n", STDOUT_FILENO))
		return (errno);
	if (parse->cmd_argv[1] == NULL)
		exit(0);
	exit_num = ft_atol(parse->cmd_argv[1], &flag);
	if (flag == 1)
	{
		if (print_builtin_error(parse->cmd_argv[0], parse->cmd_argv[1], \
								"numeric argument required\n"))
			return (errno);
		exit(255);
	}
	if (parse->cmd_argv[2] != NULL)
	{
		if (print_builtin_error(parse->cmd_argv[0], NULL, \
							"too many arguments\n"))
			return (errno);
		return (1);
	}
	exit(exit_num % 256);
}