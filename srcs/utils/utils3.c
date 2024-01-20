/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:19:39 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/20 14:45:17 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command(char *cmd)
{
	char	*builtincmd[8];
	int		i;

	i = -1;
	builtincmd[0] = "cd";
	builtincmd[1] = "echo";
	builtincmd[2] = "env";
	builtincmd[3] = "exit";
	builtincmd[4] = "export";
	builtincmd[5] = "pwd";
	builtincmd[6] = "unset";
	builtincmd[7] = NULL;
	while (builtincmd[++i])
	{
		if (!ft_strcmp(cmd, builtincmd[i]))
			return (i);
	}
	return (0);
}
