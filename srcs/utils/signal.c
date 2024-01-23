#include "minishell.h"

void	set_sigterm(void) // exit code 0
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[11C", STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT) // exit code 1
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
	struct termios	termios;

	tcgetattr(STDOUT_FILENO, &termios);
	termios.c_lflag &= ~(ECHOCTL); //제어문자가 반향되도록 한다. 이 플래그를 on 시킨 상태에서 ctrl + x를 누르면 ^X로 화면에 표시된다.
	tcsetattr(STDOUT_FILENO, 0, &termios);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}