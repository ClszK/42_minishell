/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 05:06:11 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/08 05:06:11 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_envp *env_c)
{
	char	*pwd;

	errno = 0;
	if (env_c->pwd)
		return (ft_putstr_fd(env_c->pwd, STDOUT_FILENO) \
			|| ft_putstr_fd("\n", STDOUT_FILENO));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_strerror("pwd", NULL);
		return (1);
	}
	if (ft_putstr_fd(pwd, STDOUT_FILENO) || \
		ft_putstr_fd("\n", STDOUT_FILENO))
	{
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}
