/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:50:33 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/15 22:52:03 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return (-1);
	while (*(s))
	{
		if(write(fd, s++, 1) < 0)
			return (-1);
	}
	return (0);
}