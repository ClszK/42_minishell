/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:21:16 by jeholee           #+#    #+#             */
/*   Updated: 2023/11/20 13:07:31 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_format(const char *format, int *len, va_list *ap)
{
	if (*(format) == 'c')
		return (ft_print_char(len, ap));
	else if (*(format) == 's')
		return (ft_print_s(len, ap));
	else if (*(format) == 'p')
		return (ft_print_p(len, ap));
	else if (*(format) == 'd' || *(format) == 'i')
		return (ft_print_d_i(len, ap));
	else if (*(format) == 'u')
		return (ft_print_u(len, ap));
	else if (*(format) == 'x')
		return (ft_print_low_x(len, ap));
	else if (*(format) == 'X')
		return (ft_print_up_x(len, ap));
	else if (*(format) == '%')
	{
		if (write(1, "%", 1) < 0)
			return (-1);
		++(*len);
	}
	else
		return (-1);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, format);
	while (*(format))
	{
		if (*(format) != '%')
		{
			++len;
			if (write(1, format, 1) < 0)
				return (-1);
		}
		else
		{
			if (ft_format(++format, &len, &ap) < 0)
			{
				va_end(ap);
				return (-1);
			}
		}
		++format;
	}
	va_end(ap);
	return (len);
}
