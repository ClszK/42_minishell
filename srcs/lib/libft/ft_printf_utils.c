/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 21:11:31 by jeholee           #+#    #+#             */
/*   Updated: 2023/09/15 07:53:56 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

size_t	ft_strlen_f(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	stack_fill_f(char *stack, int *n, int *top)
{
	if (*(n) == 0)
		stack[++*(top)] = '0';
	while (*(n))
	{
		stack[++*(top)] = (char)((unsigned int)*(n) % 10 + '0');
		*(n) = (int)((unsigned int)*(n) / 10);
	}
}

char	*ft_itoa_f(int n)
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
	stack_fill_f(stack, &n, &top);
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
