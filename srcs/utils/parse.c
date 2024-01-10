/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 04:21:16 by ljh               #+#    #+#             */
/*   Updated: 2024/01/11 01:16:10 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_cmdline(char *rline, t_cmdline *cmdline)
{
	int	i;

	i = -1;
	while (rline[++i])
	{

	}
}

int	char_type(char ch)
{
	return (PIPE);
}

// ls|cat >test

// ls|cat
// >test

// WORD , ", ', >, <, >>, <<, |