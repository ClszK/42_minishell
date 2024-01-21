/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:18:12 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/21 10:23:49 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_init(t_pinfo *pinfo, int cmd_argc)
{
	if (cmd_argc == 1)
	{
		pinfo->pipe_cnt = 0;
		return (0);
	}
	errno = 0;
	pinfo->pipe_cnt = cmd_argc - 1;
	printf("pipe_cnt : %d\n", cmd_argc - 1);
	if (pipe(pinfo->pfd[0]) \
		|| pipe(pinfo->pfd[1]))
		return (errno);
	return (0);
}

void	pipe_close(t_pinfo *info, int pos, int pipe_cnt)
{
	// int	i;

	// i = 0;
	// errno = 0;
	// while (i < 2)
	// {
	// 	if (i != pos)
	// 	{
	// 		printf("i != pos	%d	%d\n", i, 1);
	// 		close(info->pfd[i][1]);
	// 	}
	// 	if (i != pos - 1)
	// 	{
	// 		printf("i != pos - 1	%d	%d\n", i, 0);
	// 		close(info->pfd[i][0]);
	// 	}
	// 	i++;
	// }
	// if (errno != 0)
	// 	perror("minishell");

	close(info->pfd[0][1]);
	close(info->pfd[0][0]);
	close(info->pfd[1][0]);
	close(info->pfd[1][1]);
}
