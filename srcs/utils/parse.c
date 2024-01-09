/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 04:21:16 by ljh               #+#    #+#             */
/*   Updated: 2024/01/10 08:37:37 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_cmdline(char **argv, t_cmdline *cmdline)
{
	int	i;
	int	j;
	int	argc;

	i = 0;
	j = 0;
	argc = 0;
	while (1)
	{
		while (argv[i][j])
		{
			j++;
		}
		i++;
	}
}

// ls|cat >test

// ls|cat
// >test