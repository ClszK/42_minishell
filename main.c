#include "minishell.h"

int main(int argc, char **argv, char* envp[])
{
	// char *str;
	(void)argc;
	(void)argv;
	// str = readline("> ");
	// printf("%s", str);

	for (int i = 0; envp[i] ; i++)
		printf("%s\n", envp[i]);
}