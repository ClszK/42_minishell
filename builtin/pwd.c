#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	errno = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("minishell: %s\n", strerror(errno));
		return (errno);
	}
	if (printf("%s\n", pwd) < 0)
	{
		free(pwd);
		return (errno);
	}
	free(pwd);
	return (0);
}
