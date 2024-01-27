/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:52:23 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 19:43:12 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return (-1);
	while (*(s))
	{
		if (write(fd, s++, 1) < 0)
			return (-1);
	}
	if (write(fd, "\n", 1))
		return (-1);
	return (0);
}
