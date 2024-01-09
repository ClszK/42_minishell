/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:10:53 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/09 23:46:11 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_init(char **envp, t_envp *env_c)
{
	t_map	*map;
	int		equal;
	int		i;

	errno = 0;
	if (dlst_init(&env_c->head, &env_c->tail))
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
		if (map->key == NULL || map->val == NULL)
			exit(errno);
		dlst_add_last(env_c->tail, (t_map*)map);
	}
}
