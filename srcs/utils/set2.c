/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:45:04 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 00:59:42 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_pwd(t_envp *env_c)
{
	char	*val;

	val = expand_env_find(env_c, "PWD");
	if (val)
	{
		env_c->pwd = ft_strdup(val);
		if (env_c->pwd == NULL)
			exit(errno);
	}
}

void	envp_init(char **envp, t_envp *env_c)
{
	t_map	*map;
	int		equal;
	int		i;

	errno = 0;
	if (dlst_init(env_c))
		exit(errno);
	i = -1;
	env_c->last_stat = 0;
	while (envp[++i])
	{
		map = (t_map *)malloc(sizeof(t_map));
		if (map == NULL)
			exit(errno);
		equal = (int)(ft_strchr(envp[i], '=') - envp[i]);
		map->key = ft_substr(envp[i], 0, equal);
		map->val = ft_strdup(envp[i] + equal + 1);
		if (map->key == NULL || map->val == NULL || \
			errno || dlst_add_last(env_c, (t_map *)map))
			exit(errno);
	}
	set_env_pwd(env_c);
	map_oldpwd_find(env_c, env_c->head->next);
}
