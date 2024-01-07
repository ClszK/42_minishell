/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:53:17 by jeholee           #+#    #+#             */
/*   Updated: 2023/03/21 17:01:44 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size)
{
	void				*r_colloc;

	r_colloc = malloc(count * size);
	if (r_colloc == NULL)
		return (NULL);
	ft_bzero(r_colloc, count * size);
	return (r_colloc);
}
