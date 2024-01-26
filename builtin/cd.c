/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:02:39 by ljh               #+#    #+#             */
/*   Updated: 2024/01/26 18:02:40 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_envp *env_c, char *pwd)
{
	char	*tmp;
	int		equal;

	errno = 0;
	tmp = ft_strjoin("PWD=", pwd);
	if (pwd && tmp == NULL)
		exit(1);
	equal = find_char(tmp, '=');
	check_dup(tmp, env_c->head->next, equal);
	free(tmp);
	if (env_c->pwd)
	{
		free(env_c->pwd);
		env_c->pwd = ft_strdup(pwd);
		if (env_c->pwd == NULL)
			exit(errno);
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
		exit(errno);
	equal = find_char(tmp, '=');
	check_dup(tmp, env_c->head->next, equal);
	free(tmp);
}

int	change_dir(t_envp *env_c, char *path)
{
	char	*pwd;

	errno = 0;
	if (chdir(path))
	{
		print_strerror("cd", path);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL && errno == ENOENT)
	{
		print_strerror("cd: error retrieving current directory", \
					"getcwd: cannot access parent directories");
		pwd = ft_strjoin(env_c->pwd, "/..");
		if (pwd == NULL)
			exit(errno);
	}
	else if (pwd == NULL)
	{
		print_strerror("cd", NULL);
		return (1);
	}
	change_oldpwd(env_c);
	change_pwd(env_c, pwd);
	return (0);
}

int	cd_oldpwd(t_envp *env_c, char *path)
{
	if (!path || !*path)
	{
		print_builtin_error("cd", NULL, "OLDPWD not set\n");
		return (1);
	}
	if (!change_dir(env_c, path))
		if (ft_putstr_fd(env_c->pwd, 1) || ft_putstr_fd("\n", 1))
			return (1);
	return (0);
}

int	builtin_cd(t_parse *parse, t_envp *env_c)
{
	char	*path;

	if (parse->cmd_argv == NULL || parse->cmd_argv[1][0] == '\0')
		return (0);
	if (parse->cmd_argv[1] == NULL || !ft_strcmp(parse->cmd_argv[1], "--"))
	{
		path = expand_env_find(env_c, "HOME");
		if (!path || !*path)
		{
			print_builtin_error("cd", NULL, "HOME not set\n");
			return (1);
		}
		return (change_dir(env_c, path));
	}
	if (!ft_strcmp(parse->cmd_argv[1], "-"))
	{
		path = expand_env_find(env_c, "OLDPWD");
		return (cd_oldpwd(env_c, path));
	}
	return (change_dir(env_c, parse->cmd_argv[1]));
}
