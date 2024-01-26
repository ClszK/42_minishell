/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:12:20 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/15 22:34:48 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	stack_fill(char *stack, int *n, int *top)
{
	if (*(n) == 0)
		stack[++*(top)] = '0';
	while (*(n))
	{
		stack[++*(top)] = (char)((unsigned int)*(n) % 10 + '0');
		*(n) = (int)((unsigned int)*(n) / 10);
	}
}

char	*ft_itoa(int n)
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
	stack_fill(stack, &n, &top);
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
