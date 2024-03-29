/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:42:10 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 18:24:21 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_elem_free(void *elem)
{
	t_token	*token;

	token = (t_token *)elem;
	free(token->str);
	free(token->env_val);
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
	parse->cmd_argv = NULL;
	dlst_del_all(parse->std_lst, token_elem_free);
	free(parse->std_lst);
	parse->std_lst = NULL;
	if (parse->cmd_path)
		free(parse->cmd_path);
	parse->cmd_path = NULL;
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
		dlst_del_all(&sh->heredoc, NULL);
		free(sh->rline);
	}
	if (env_c)
		dlst_del_all(env_c, map_elem_free);
}
