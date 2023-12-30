/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:56:04 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/15 22:59:23 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	*hex_table;
	int		stack[11];
	int		top;

	hex_table = "0123456789";
	top = -1;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	while (n)
	{
		stack[++top] = (unsigned int)n % 10;
		n = (unsigned int)n / 10;
	}
	while (top > -1)
		write(fd, &hex_table[stack[top--]], 1);
}
