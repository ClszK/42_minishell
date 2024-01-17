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

int	builtin_pwd(void)
{
	char	*pwd;

	errno = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_strerror("minishell", "PWD");
		return (errno);
	}
	if (ft_putstr_fd(pwd, STDOUT_FILENO) || \
		ft_putstr_fd("\n", STDOUT_FILENO))
	{
		free(pwd);
		return (errno);
	}
	free(pwd);
	return (0);
}
