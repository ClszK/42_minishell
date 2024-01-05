#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	errno = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		if (printf("minishell: %s\n", strerror(errno)) < 0)
			perror("minishell: "); // printf 예외처리하기
		return (errno);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}