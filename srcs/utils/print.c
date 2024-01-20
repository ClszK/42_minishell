/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:28:15 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/20 12:17:10 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 임시 exit **/
void	perror_exit(char *progname)
{
	perror(progname);
	exit(EXIT_FAILURE);
}

int	print_strerror(char *progname, char *str)
{
	if (ft_putstr_fd(progname, STDERR_FILENO) || \
		ft_putstr_fd(": ", STDERR_FILENO) || \
		ft_putstr_fd(str, STDERR_FILENO) || \
		ft_putstr_fd(": ", STDERR_FILENO) || \
		ft_putstr_fd(strerror(errno), STDERR_FILENO) || \
		ft_putstr_fd("\n", STDERR_FILENO))
		return (errno);
	return (0);
}

int	print_builtin_error(char *cmd, char *arg, char *error)
{
	if	(ft_putstr_fd("minishell: ", STDERR_FILENO) || \
		ft_putstr_fd(cmd, STDERR_FILENO) || \
		ft_putstr_fd(": ", STDERR_FILENO) || \
		(arg != NULL && ft_putstr_fd(arg, STDERR_FILENO)) || \
		(arg != NULL && ft_putstr_fd(": ", STDERR_FILENO)) || \
		ft_putstr_fd(error, STDERR_FILENO))
		return (errno);
	return (0);
}

/** 임시 exit **/
void	error_exit(char *progname, char *str, char *str2, int code)
{
	ft_putstr_fd(progname, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (str2 != NULL)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(code);
}
