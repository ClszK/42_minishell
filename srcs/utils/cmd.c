/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/20 14:42:05 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commandline_excute(t_shinfo *sh)
{
	int		builtin_index;
	t_envp	*env_c;
	t_parse	*parse;

	parse = sh->alz.head->next->elem;
	env_c = &sh->env_c;
	builtin_index = is_builtin_command(parse->cmd_argv[0]);
	if (builtin_index == 0)
		builtin_cd(parse, env_c);
	else if (builtin_index == 1)
		builtin_echo(parse);
	else if (builtin_index == 2)
		builtin_env(env_c);
	else if (builtin_index == 3)
		builtin_exit(parse);
	else if (builtin_index == 4)
		builtin_export(parse, env_c);
	else if (builtin_index == 5)
		builtin_pwd();
	else if (builtin_index == 6)
		builtin_unset(parse, env_c);
}