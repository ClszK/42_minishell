/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:10:53 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 00:45:41 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmdline_init(t_cmdline *cmdline)
{
	errno = 0;
	if (dlst_init(cmdline))
		exit(errno);
}

void	analyze_init(t_analyze *alz)
{
	errno = 0;
	if (dlst_init(alz))
		exit(errno);
}

t_stdio	*stdio_init(void)
{
	t_stdio	*lst;

	errno = 0;
	lst = malloc(sizeof(t_stdio));
	if (lst == NULL || dlst_init(lst))
		exit(errno);
	return (lst);
}

void	shinfo_init(t_shinfo *sh)
{
	sh->rline = NULL;
	cmdline_init(&sh->cmdline);
	analyze_init(&sh->alz);
}
