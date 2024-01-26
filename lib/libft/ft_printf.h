/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 04:07:33 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/07 23:27:17 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_format(const char *format, int *len, va_list *ap);
int		ft_print_char(int *len, va_list *ap);
int		ft_print_s(int *len, va_list *ap);
int		ft_print_p(int *len, va_list *ap);
int		ft_print_d_i(int *len, va_list *ap);
int		ft_print_u(int *len, va_list *ap);
int		ft_print_low_x(int *len, va_list *ap);
int		ft_print_up_x(int *len, va_list *ap);
int		ft_putnbr_base(int nb, char *base, int *len);
size_t	ft_strlen_f(const char *s);
char	*ft_itoa_f(int n);

int		addr_print(void *addr, int *len);

#endif