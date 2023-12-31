/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 05:03:19 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/10 04:33:41 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(t_cmd *parse, int *n_flag)
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

int	builtin_echo(t_cmd *parse)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	errno = 0;
	i = check_option(parse, &n_flag);
	while (parse->cmd_argv[i])
	{
		if (printf("%s", parse->cmd_argv[i++]) < 0)
			return (errno);
		if (parse->cmd_argv[i])
			if (printf(" ") < 0)
				return (errno);
	}
	if (!n_flag)
		if (printf("\n") < 0)
			return (errno);
	return (0);
}