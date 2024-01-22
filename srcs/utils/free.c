/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:42:10 by ljh               #+#    #+#             */
/*   Updated: 2024/01/23 05:23:27 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_elem_free(void *elem)
{
	t_token	*token;

	token = (t_token *)elem;
	free(token->str);
	free(token);
}

void	parse_elem_free(void *elem)
{
	t_parse	*parse;
	int		i;

	parse = (t_parse *)elem;
	i = -1;
	while (parse->cmd_argv[++i])
		free(parse->cmd_argv[i]);
	free(parse->cmd_argv);
	dlst_del_all(parse->stdin_lst, token_elem_free);
	dlst_del_all(parse->stdout_lst, token_elem_free);
	free(parse->stdin_lst);
	free(parse->stdout_lst);
	if (parse->cmd_path)
		free(parse->cmd_path);
	free(parse);
}

void	map_elem_free(void *elem)
{
	t_map	*map;

	map = (t_map *)elem;
	free(map->key);
	free(map->val);
	free(map);
}

void	split_free(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

void	shinfo_free(t_shinfo *sh, t_envp *env_c)
{
	if (sh)
	{
		dlst_del_all(&sh->cmdline, token_elem_free);
		dlst_del_all(&sh->alz, parse_elem_free);
		free(sh->rline);
	}
	if (env_c)
		dlst_del_all(env_c, map_elem_free);
}