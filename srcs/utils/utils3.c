/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:19:39 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/24 17:05:41 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command(char *cmd)
{
	char	*builtincmd[8];
	int		i;

	i = -1;
	if (cmd == NULL)
		return (0);
	while (cmd[++i])
		cmd[i] = ft_tolower(cmd[i]);
	builtincmd[0] = "cd";
	builtincmd[1] = "echo";
	builtincmd[2] = "env";
	builtincmd[3] = "exit";
	builtincmd[4] = "export";
	builtincmd[5] = "pwd";
	builtincmd[6] = "unset";
	builtincmd[7] = NULL;
	i = -1;
	while (builtincmd[++i])
	{
		if (!ft_strcmp(cmd, builtincmd[i]))
			return (i + 1);
	}
	return (0);
}

int	is_include_pipe(t_analyze *alz)
{
	if (alz->lst_size > 1)
		return (1);
	return (0);
}

int	is_file_access(char *filename, int mode)
{
	errno = 0;
	if (access(filename, mode) == 0)
		return (1);
	if (errno != 0)
		print_strerror(NULL, filename);
	return (0);
}
