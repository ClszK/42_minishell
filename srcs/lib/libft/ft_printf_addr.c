/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 04:51:52 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 07:51:51 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	addr_print(void *addr, int *len)
{
	unsigned long long	addr_long;
	int					stack[18];
	int					top;
	char				*hex_table;

	top = 0;
	hex_table = "0123456789abcdefx";
	addr_long = (unsigned long long)addr;
	if (addr_long == 0)
		stack[top++] = 0;
	while (addr_long)
	{
		stack[top++] = addr_long % 16;
		addr_long /= 16;
	}
	stack[top++] = 16;
	stack[top++] = 0;
	*(len) += top;
	while (top > 0)
		if (write(1, &hex_table[stack[--top]], 1) < 0)
			return (-1);
	return (1);
}
