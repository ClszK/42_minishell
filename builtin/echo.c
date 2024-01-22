/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 05:03:19 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/20 14:48:07 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(t_parse *parse, int *n_flag)
{
	int	i;
	int	j;

	i = 0;
	while (parse->cmd_argv[++i])
	{
		if (parse->cmd_argv[i][0] == '-')
		{
			j = 1;
			while (parse->cmd_argv[i][j] == 'n')
				j++;
			if (parse->cmd_argv[i][j] || j == 1)
				break ;
			*n_flag = 1;
		}
		else
			break ;
	}
	return (i);
}

int	builtin_echo(t_parse *parse)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = check_option(parse, &n_flag);
	while (parse->cmd_argv[i])
	{
		if (ft_putstr_fd(parse->cmd_argv[i++], STDOUT_FILENO))
			return (1);
		if (parse->cmd_argv[i])
			if (ft_putstr_fd(" ", STDOUT_FILENO))
				return (1);
	}
	if (!n_flag)
		if (ft_putstr_fd("\n", STDOUT_FILENO))
			return (1);
	return (0);
}
