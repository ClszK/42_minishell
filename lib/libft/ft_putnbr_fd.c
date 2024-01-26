/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:56:04 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/23 09:51:18 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr_fd(int n, int fd)
{
	char	*hex_table;
	int		stack[11];
	int		top;

	hex_table = "0123456789";
	top = -1;
	if (n == 0)
	{
		if (write(fd, "0", 1) < 0)
			return (-1);
	}
	if (n < 0)
	{
		if (write(fd, "-", 1) < 0)
			return (-1);
		n *= -1;
	}
	while (n)
	{
		stack[++top] = (unsigned int)n % 10;
		n = (unsigned int)n / 10;
	}
	while (top > -1)
		if (write(fd, &hex_table[stack[top--]], 1) < 0)
			return (-1);
	return (0);
}
