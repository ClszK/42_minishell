#include "minishell.h"

void	change_pwd(t_envp *env_c, char *pwd)
{
	char	*tmp;
	int		equal;

	tmp = ft_strjoin("PWD=", pwd);
	if (pwd && tmp == NULL)
		exit(1);
	equal = find_char(tmp, '=');
	check_dup(tmp, env_c, equal);
	printf("PWD: %s\n", expand_env_find(env_c, "PWD")); //del
	free(tmp);
	if (env_c->pwd)
	{
		free(env_c->pwd);
		env_c->pwd = ft_strdup(pwd);
	}
	free(pwd);
}

void	change_oldpwd(t_envp *env_c)
{
	char	*tmp;
	int		equal;

	errno = 0;
	tmp = ft_strjoin("OLDPWD=", env_c->pwd);
	if (env_c->pwd && tmp == NULL)
		exit(1);
	equal = find_char(tmp, '=');
	check_dup(tmp, env_c, equal);
	printf("OLD: %s\n", expand_env_find(env_c, "OLDPWD")); //del
	free(tmp);
}

int	change_dir(t_envp *env_c, char *path)
{
	char	*pwd;

	errno = 0;
	if (chdir(path))
		return (print_strerror("cd", path));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)         
	{
		if (errno == ENOENT)
		{
			print_strerror("cd: error retrieving current directory", \
						"getcwd: cannot access parent directories");
			pwd = ft_strjoin(env_c->pwd, "/..");
			if (pwd == NULL)
				exit(1);
		}
		else
			return (print_strerror("cd", NULL));
	}
	change_oldpwd(env_c);
	change_pwd(env_c, pwd);
	return (0);
}

int	builtin_cd(t_parse *parse, t_envp *env_c)
{
	char	*path;

	errno = 0;
	if (parse->cmd_argv[1] == NULL || !ft_strcmp(parse->cmd_argv[1], "--"))
	{
		path = expand_env_find(env_c, "HOME");
		if (!path || !*path)
			return (print_builtin_error("cd", NULL, "HOME not set\n"));
		return (change_dir(env_c, path));
	}
	if (!ft_strcmp(parse->cmd_argv[1], "-"))
	{
		path = expand_env_find(env_c, "OLDPWD");
		if (!path || !*path)
			return (print_builtin_error("cd", NULL, "OLDPWD not set\n"));
		return (change_dir(env_c, path));
	}
	return (change_dir(env_c, parse->cmd_argv[1]));
}