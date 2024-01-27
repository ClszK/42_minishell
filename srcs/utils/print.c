/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:28:15 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 12:05:31 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 임시 exit **/
void	perror_exit(char *progname)
{
	perror(progname);
	exit(EXIT_FAILURE);
}

int	print_strerror(char *cmd, char *arg)
{
	if (ft_putstr_fd("minishell: ", STDERR_FILENO) || \
		(cmd && ft_putstr_fd(cmd, STDERR_FILENO)) || \
		(cmd && ft_putstr_fd(": ", STDERR_FILENO)) || \
		(arg && ft_putstr_fd(arg, STDERR_FILENO)) || \
		(arg && ft_putstr_fd(": ", STDERR_FILENO)) || \
		ft_putstr_fd(strerror(errno), STDERR_FILENO) || \
		ft_putstr_fd("\n", STDERR_FILENO))
		return (1);
	return (0);
}

int	print_builtin_error(char *cmd, char *arg, char *error)
{
	if (ft_putstr_fd("minishell: ", STDERR_FILENO) || \
		(cmd && ft_putstr_fd(cmd, STDERR_FILENO)) || \
		(cmd && ft_putstr_fd(": ", STDERR_FILENO)) || \
		(arg && ft_putstr_fd(arg, STDERR_FILENO)) || \
		(arg && ft_putstr_fd(": ", STDERR_FILENO)) || \
		ft_putstr_fd(error, STDERR_FILENO))
		return (1);
	return (0);
}

int	print_syntax_error(int type)
{
	char	*type_str[10];

	type_str[0] = NULL;
	type_str[1] = NULL;
	type_str[2] = "|";
	type_str[3] = ">";
	type_str[4] = ">>";
	type_str[5] = "<";
	type_str[6] = "<<";
	type_str[7] = "newline";
	type_str[8] = "'";
	type_str[9] = "\"";
	if (ft_putstr_fd("minishell: ", STDERR_FILENO) || \
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO) || \
		ft_putstr_fd(type_str[type], STDERR_FILENO) || \
		ft_putstr_fd("'\n", STDERR_FILENO))
		return (1);
	return (0);
}

void	print_cmd_path_error(char *cmd, t_envp *env_c)
{
	if (errno == EACCES)
	{
		print_strerror(cmd, NULL);
		env_c->last_stat = 126;
	}
	else
	{
		print_builtin_error(cmd, NULL, "command not found\n");
		env_c->last_stat = 127;
	}
}
