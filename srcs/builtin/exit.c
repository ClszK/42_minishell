/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:02:46 by ljh               #+#    #+#             */
/*   Updated: 2024/01/29 01:11:58 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_check_argv(t_parse *parse, char **argv)
{
	int	exit_num;
	int	flag;

	flag = 0;
	errno = 0;
	*argv = ft_strtrim(parse->cmd_argv[1], " ");
	if (*argv == NULL)
		exit(errno);
	exit_num = ft_atol(*argv, &flag);
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
	long	exit_num;
	char	*argv;

	if (!is_fork && (ft_putstr_fd("exit", STDOUT_FILENO) || \
		ft_putstr_fd("\n", STDOUT_FILENO)))
		return (1);
	if (parse->cmd_argv[1] == NULL)
		exit(0);
	if (!ft_strcmp(parse->cmd_argv[1], "-9223372036854775808") \
		&& parse->cmd_argv[2] == NULL)
		exit (0);
	else if (ft_strcmp(parse->cmd_argv[1], "-9223372036854775808"))
		exit_num = exit_check_argv(parse, &argv);
	if (parse->cmd_argv[2] != NULL)
	{
		print_builtin_error(parse->cmd_argv[0], NULL, "too many arguments\n");
		free(argv);
		return (1);
	}
	exit(exit_num % 256);
}
