/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:10:53 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/11 01:39:59 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_init(char **envp, t_envp *env_c)
{
	t_map	*map;
	int		equal;
	int		i;

	errno = 0;
	if (dlst_init(env_c))
		exit(errno);
	i = -1;
	while (envp[++i])
	{
		map = (t_map*)malloc(sizeof(t_map));
		if (map == NULL)
			exit(errno);
		equal = (int)(ft_strchr(envp[i], '=') - envp[i]);
		map->key = ft_substr(envp[i], 0, equal);
		map->val = ft_strdup(envp[i] + equal + 1);
		if (map->key == NULL || map->val == NULL || \
			dlst_add_last(env_c, (t_map*)map))
			exit(errno);
	}
	map = (t_map*)malloc(sizeof(t_map));
	if (map == NULL)
		exit(errno);
	map->key = ft_strdup("OLDPWD"); //없으면 추가되게
	map->val = NULL;
	if (map->key == NULL || \
		dlst_add_last(env_c, (t_map*)map))
		exit(errno);
}

void	cmdline_init(t_cmdline *cmdline)
{
	errno = 0;
	if (dlst_init(cmdline))
		exit(errno);
}