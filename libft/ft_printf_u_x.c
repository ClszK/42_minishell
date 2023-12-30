/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 03:45:56 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 07:53:37 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

void	stack_fill_u(char *stack, unsigned int *n, int *top)
{
	if (*(n) == 0)
		stack[++*(top)] = '0';
	while (*(n))
	{
		stack[++*(top)] = (char)(*(n) % 10 + '0');
		*(n) = *(n) / 10;
	}
}

char	*ft_itoa_u(unsigned int n)
{
	char	stack[33];
	int		top;
	int		sign;
	char	*nbr;

	top = -1;
	sign = 1;
	if (n < 0)
	{
		n *= -1;
		sign = -1;
	}
	stack_fill_u(stack, &n, &top);
	if (sign == -1)
		stack[++top] = '-';
	nbr = (char *)malloc(sizeof(char) * (top + 2));
	if (nbr == NULL)
		return (NULL);
	while (top > -1)
		*(nbr + (n++)) = stack[top--];
	*(nbr + n) = '\0';
	return (nbr);
}

int	ft_print_u(int *len, va_list *ap)
{
	int		u;
	int		u_len;
	char	*u_str;

	u = (unsigned int)va_arg(*ap, int);
	u_str = ft_itoa_u((unsigned int)u);
	if (u_str == NULL)
		return (-1);
	u_len = ft_strlen_f(u_str);
	if (write(1, u_str, u_len) < 0)
	{
		free(u_str);
		return (-1);
	}
	free(u_str);
	*(len) += u_len;
	return (1);
}

int	ft_print_low_x(int *len, va_list *ap)
{
	int	low_x;

	low_x = (int)va_arg(*ap, int);
	if (ft_putnbr_base(low_x, "0123456789abcdef", len) < 0)
		return (-1);
	return (1);
}

int	ft_print_up_x(int *len, va_list *ap)
{
	int	up_x;

	up_x = (int)va_arg(*ap, int);
	if (ft_putnbr_base(up_x, "0123456789ABCDEF", len) < 0)
		return (-1);
	return (1);
}
