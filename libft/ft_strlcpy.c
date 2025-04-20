/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:18:45 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/05 17:51:27 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cpy_index;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	cpy_index = 0;
	while (cpy_index + 1 < size && src[cpy_index] != '\0')
	{
		dest[cpy_index] = src[cpy_index];
		cpy_index++;
	}
	dest[cpy_index] = '\0';
	return (src_len);
}
