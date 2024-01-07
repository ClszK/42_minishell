/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:45:12 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 08:04:14 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_putnbr_base(int nb, char *base, int *len)
{
	int	base_len;
	int	stack[33];
	int	top;

	base_len = (int)ft_strlen_f(base);
	top = -1;
	if (nb == 0)
	{
		if (write(1, &base[0], 1) < 0)
			return (-1);
		*(len) += 1;
	}
	while (nb)
	{
		stack[++top] = (int)((unsigned int)nb % base_len);
		nb = (int)((unsigned int)nb / base_len);
	}
	*(len) += top + 1;
	while (top > -1)
		if (write(1, &base[stack[top--]], 1) < 0)
			return (-1);
	return (1);
}
