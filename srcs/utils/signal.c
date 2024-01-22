#include "minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = signo;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		g_signo = signo;
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	sig_handler_sigquit(int signo)
// {

// }

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	// SIG_IGN
}