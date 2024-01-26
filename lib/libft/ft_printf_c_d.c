/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 03:44:54 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 07:52:54 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_print_char(int *len, va_list *ap)
{
	char	c;

	c = (char)va_arg(*ap, int);
	if (write(1, &c, 1) < 0)
		return (-1);
	++(*len);
	return (1);
}

int	ft_print_s(int *len, va_list *ap)
{
	char	*str;
	size_t	s_len;

	str = (char *)va_arg(*ap, char *);
	if (str == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		*(len) += 6;
		return (1);
	}
	s_len = ft_strlen_f(str);
	if (write(1, str, s_len) < 0)
		return (-1);
	*(len) += s_len;
	return (1);
}

int	ft_print_p(int *len, va_list *ap)
{
	void	*addr;

	addr = (void *)va_arg(*ap, void *);
	if (addr_print(addr, len) < 0)
		return (-1);
	return (1);
}

int	ft_print_d_i(int *len, va_list *ap)
{
	int		d_i;
	int		d_i_len;
	char	*d_i_str;

	d_i = (int)va_arg(*ap, int);
	d_i_str = ft_itoa_f(d_i);
	if (d_i_str == NULL)
		return (-1);
	d_i_len = ft_strlen_f(d_i_str);
	if (write(1, d_i_str, d_i_len) < 0)
	{
		free(d_i_str);
		return (-1);
	}
	free(d_i_str);
	*(len) += d_i_len;
	return (1);
}
