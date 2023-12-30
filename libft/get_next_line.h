/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:57:57 by stack             #+#    #+#             */
/*   Updated: 2023/09/15 01:07:30 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# if BUFFER_SIZE > 4294967295
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 49152
# endif

# if OPEN_MAX <= 0
#  undef OPEN_MAX
#  define OPEN_MAX 0
# elif OPEN_MAX >= 2147483647
#  undef OPEN_MAX
#  define OPEN_MAX 0
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list_g
{
	char			*content;
	long long		len;
	long long		lnpos;
	size_t			totallen;
	struct s_list_g	*next;
}	t_list_g;

char		*get_next_line(int fd);
char		*gnl_lstcat(t_list_g **tmp);
int			read_line(t_list_g **tmp, char *buffer, ssize_t readsize);
char		*gnl_lstcat_2(t_list_g **tmp, t_list_g *node, char *str);

t_list_g	*gnl_lstnew(char *content);
int			gnl_lstadd_back(t_list_g **lst, t_list_g *new);
void		gnl_lstclear(t_list_g **lst, char *str);
t_list_g	*gnl_lstlast(t_list_g *lst);
char		*gnl_strncat(char *dest, const char *src, ssize_t nb, int flag);

#endif