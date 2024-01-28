/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:53:21 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/28 22:59:29 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigterm(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[11C", STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(0);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 1;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	set_terminal(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_child(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signal(void)
{
	set_terminal(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
