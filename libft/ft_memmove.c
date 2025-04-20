/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:52:17 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/01 13:52:17 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*temp;

	if (dest == src)
		return (dest);
	psrc = (unsigned char *)src;
	temp = (unsigned char *)dest;
	if (dest <= src)
	{
		while (n-- > 0)
			*(temp++) = *(psrc++);
	}
	else
	{
		temp += n;
		psrc += n;
		while (n-- > 0)
			*(--temp) = *(--psrc);
	}
	return (dest);
}
