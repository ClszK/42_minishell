#include "minishell.h"

/*
	// exit code 0 //ctrl + d
*/
void	set_sigterm(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[11C", STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
}

/*
	//sigint 처리 
		// exit code 1
*/
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

/*
	//메인 시그널 처리 자식 프로세스에서 모든 작업 끝나면다시 셋해주기
*/
void	set_signal(void)
{
	set_terminal(1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
	//fork 하기 전에 모든 시그널 안받게함
*/
void	set_signal_child(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*
	//다시 모든 시그널 받게 만들어줌 마지막에 핸들러 적용 안함
*/
void	restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
	//heredoc에서 끝나게 해줌
*/
void	heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
}

/*
	//here doc 실행될 때 
*/
void	heredoc_signal(void) 
{
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_terminal(int flag) 
{
	struct termios	terminal;

	if (flag == 1) // 부모 프로세스에서 ^c출력 안되게
	{
		tcgetattr(STDOUT_FILENO, &terminal);
		terminal.c_lflag &= ~(ECHOCTL); //제어문자가 반향되도록 한다. 이 플래그를 on 시킨 상태에서 ctrl + x를 누르면 ^X로 화면에 표시된다.
		tcsetattr(STDOUT_FILENO, 0, &terminal);	
	}
	else if (flag == 0) // 다시 출력되게 만들어줌 a.out 실행될 때?
	{
		tcgetattr(STDOUT_FILENO, &terminal);
		terminal.c_lflag |= (ECHOCTL); //제어문자가 반향되도록 한다. 이 플래그를 on 시킨 상태에서 ctrl + x를 누르면 ^X로 화면에 표시된다.
		tcsetattr(STDOUT_FILENO, 0, &terminal);	
	}
}

void	is_fork_signal(int status) //wait 반환값 확인
{
	int	signo;

	signo = (status & 0x7f);
	if (signo > 0)
	{
		if (signo == 2) //130
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (signo == 3) //131
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	}
}