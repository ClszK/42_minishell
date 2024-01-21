/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 04:10:53 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/21 07:40:48 by jeholee          ###   ########.fr       */
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
	env_c->pwd = ft_strdup(expand_env_find(env_c, "PWD"));
	if (env_c->pwd == NULL)
		exit(errno);
	map_oldpwd_find(env_c);
}

void	cmdline_init(t_cmdline *cmdline)
{
	errno = 0;
	if (dlst_init(cmdline))
		exit(errno);
}

void	analyze_init(t_analyze *alz)
{
	errno = 0;
	if (dlst_init(alz))
		exit(errno);
}

t_stdio	*stdio_init(void)
{
	t_stdio	*lst;

	errno = 0;
	lst = malloc(sizeof(t_stdio));
	if (lst == NULL || dlst_init(lst))
		exit(errno);
	return (lst);
}

void	shinfo_init(t_shinfo *sh)
{
	sh->rline = NULL;
	cmdline_init(&sh->cmdline);
	analyze_init(&sh->alz);
}