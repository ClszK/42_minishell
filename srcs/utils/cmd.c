/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:06:38 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/20 21:03:22 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_complex(void)
{
	return ;
}

void	command_excute_temporary(t_shinfo *sh)
{
	int		builtin_idx;
	t_envp	*env_c;
	t_parse	*parse;

	parse = sh->alz.head->next->elem;
	env_c = &sh->env_c;
	builtin_idx = 0;
	if (parse->cmd_path)
		builtin_idx = is_builtin_command(parse->cmd_path);
	command_excute_builtin(parse, env_c, builtin_idx);
}

void	command_excute_builtin(t_parse *parse, t_envp *env_c, int builtin_idx)
{
	if (builtin_idx == 0)
		builtin_cd(parse, env_c);
	else if (builtin_idx == 1)
		builtin_echo(parse);
	else if (builtin_idx == 2)
		builtin_env(env_c);
	else if (builtin_idx == 3)
		builtin_exit(parse);
	else if (builtin_idx == 4)
		builtin_export(parse, env_c);
	else if (builtin_idx == 5)
		builtin_pwd();
	else if (builtin_idx == 6)
		builtin_unset(parse, env_c);
}

void	command_fork(t_analyze *alz, t_envp *env_c)
{
	int			last_status;
	int			i;
	t_node		*parse_node;
	t_pinfo		pinfo;
	
	parse_node = alz->head->next;
	if (pipe_init(&pinfo, alz->lst_size))
		exit(errno);
	i = -1;
	while (++i < alz->lst_size)
	{
		errno = 0;
		pid = fork();
		if (pid < 0)
			perror_exit("minishell");
		else if (pid == 0)
			child_process(parse->elem, env_c, i);
		pinfo.last_pid = pinfo.pid;
		parse_node = parse_node->next;
	}
	wait_child();
}

void	command_excute(t_shinfo *sh)
{
	t_analyze	*alz;
	t_parse		*parse;
	t_envp		*env_c;
	int			builtin_idx;

	alz = &sh->alz;
	if (is_include_pipe(alz))
		command_complex();
	else
	{
		parse = alz->head->next->elem;
		env_c = &sh->env_c;
		builtin_idx = 0;
		if (parse->cmd_path)
			builtin_idx = is_builtin_command(parse->cmd_path);
		if (is_builtin_command(parse->cmd_path))
			command_excute_builtin(parse, env_c, builtin_idx);
		else
			command_fork(alz, env_c);
	}
}