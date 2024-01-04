/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:10:53 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/05 04:43:25 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* envp 안의 PATH 문자열을 찾고, PATH= 이후 문자열부터 :를 기준으로 Split한 PATH를 반환. */
char	**find_path(char *envp[])
{
	int		i;
	char	**path;

	i = -1;
	errno = 0;
	path = NULL;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			path = ft_split(envp[i] + 5, ':');
			if (path == NULL && errno != 0)
				perror_exit("minishell");
			return (path);
		}
	}
	return (path);
}

/* envp 안의 name을 찾고 name= 이후 문자열을 strdup을 담은 PATH를 반환.  */
char	*find_envp(char *envp[], char *name)
{
	int		i;
	int		name_len;
	char	*path;

	i = -1;
	name_len = ft_strlen(name);
	errno = 0;
	path = NULL;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], name, name_len))
		{
			path = ft_strdup(envp[i] + name_len + 1);
			if (path == NULL && errno != 0)
				perror_exit("minishell");
			return (path);
		}
	}
	return (path);
}

void	set_envp(char *envp[], t_envp *shell)
{
	shell->path = find_path(envp);
	shell->home = find_envp(envp, "HOME");
	shell->pwd = find_envp(envp, "PWD");
	shell->oldpwd = NULL;
}
