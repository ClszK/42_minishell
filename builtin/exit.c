#include "minishell.h"

int	exit_check_argv(t_parse *parse, char *argv)
{
	int	exit_num;
	int	flag;

	flag = 0;
	exit_num = ft_atol(argv, &flag);
	if (flag)
	{
		if (print_builtin_error(parse->cmd_argv[0], parse->cmd_argv[1], \
								"numeric argument required\n"))
			return (1);
		exit(255);
	}
	return (exit_num);
}

int	builtin_exit(t_parse *parse, int is_fork)
{
	int		exit_num;
	char	*argv;

	errno = 0;
	if (!is_fork && (ft_putstr_fd("exit", STDOUT_FILENO) || \
		ft_putstr_fd("\n", STDOUT_FILENO)))
		return (1);
	if (parse->cmd_argv[1] == NULL)
		exit(0);
	argv = ft_strtrim(parse->cmd_argv[1], " ");
	if (argv == NULL)
		exit(errno);
	exit_num = exit_check_argv(parse, argv);
	if (parse->cmd_argv[2] != NULL)
	{
		print_builtin_error(parse->cmd_argv[0], NULL, "too many arguments\n");
		free(argv);
		return (1);
	}
	exit(exit_num % 256);
}
