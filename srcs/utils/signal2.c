/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:53:21 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/28 23:00:00 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_terminal(int flag)
{
	struct termios	terminal;

	if (flag == 1)
	{
		tcgetattr(STDOUT_FILENO, &terminal);
		terminal.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDOUT_FILENO, 0, &terminal);
	}
	else if (flag == 0)
	{
		tcgetattr(STDOUT_FILENO, &terminal);
		terminal.c_lflag |= (ECHOCTL);
		tcsetattr(STDOUT_FILENO, 0, &terminal);
	}
}

void	is_fork_signal(int status, int last_status)
{
	int	signo;

	signo = (status & 0x7f);
	if (status == last_status)
	{
		if (signo > 0)
		{
			if (signo == 2)
			{
				g_signo = 2;
				ft_putstr_fd("\n", STDERR_FILENO);
			}
			else if (signo == 3)
			{
				g_signo = 3;
				ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			}
		}
	}
	else
		if (signo == 2)
			ft_putstr_fd("\n", STDOUT_FILENO);
}
