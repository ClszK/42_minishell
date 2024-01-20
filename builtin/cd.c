#include "minishell.h"


int	change_pwd(t_envp *env_c, char *oldpwd)
{
	char	*tmp;
	char	*pwd;
	int		equal;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	equal = find_char(tmp, '=');
	check_dup(tmp, env_c, equal);
	printf("OLD: %s\n", tmp);
	free(tmp);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_strerror("cd", NULL);
		return (1);
	}
	tmp = ft_strjoin("PWD=", pwd);
	equal = find_char(tmp, '=');
	check_dup(tmp, env_c, equal);
	printf("PWD: %s\n", tmp);
	free(pwd);
	free(tmp);
	return (0);
}

//ENOENT 
// cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
int	cd_home(t_envp *env_c)
{
	char	*path;
	char	*oldpwd;

	path = expand_env_find(env_c, "HOME");
	if (!path || !*path)
	{
		print_builtin_error("cd", NULL, "HOME not set\n");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		print_strerror("cd", NULL);
		return (1);
	}
	if (chdir(path))
	{
		print_strerror("cd", "path");
		free(oldpwd);
		return (1);
	}
	return (change_pwd(env_c, oldpwd));
}

int	builtin_cd(t_parse *parse, t_envp *env_c)
{
	char	*path;
	char	*oldpwd;

	errno = 0;
	if (parse->cmd_argv[1] == NULL || !ft_strcmp(parse->cmd_argv[1], "--"))
		return (cd_home(env_c));
	// if (!ft_strcmp(parse->cmd_argv[1], "-"))
	// {

	// }
}