#include "minishell.h"

int	builtin_exit(t_parse *parse)
{
	int	flag;
	int	exit_num;

	flag = 0;
	if (ft_putstr_fd("exit", STDOUT_FILENO) || \
		ft_putstr_fd("\n", STDOUT_FILENO))
		return (1);
	if (parse->cmd_argv[1] == NULL)
		exit(0);
	exit_num = ft_atol(parse->cmd_argv[1], &flag);
	if (flag == 1)
	{
		if (print_builtin_error(parse->cmd_argv[0], parse->cmd_argv[1], \
								"numeric argument required\n"))
			return (1);
		exit(255);
	}
	if (parse->cmd_argv[2] != NULL)
		return (print_builtin_error(parse->cmd_argv[0], NULL, \
							"too many arguments\n"));
	exit(exit_num % 256);
}