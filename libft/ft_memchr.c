/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:19:37 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/07 16:28:04 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	size_t			index;

	ps = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (ps[index] == (unsigned char)c)
			return (ps + index);
		index++;
	}
	return (0);
}
