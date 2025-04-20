/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:20:51 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/05 18:02:06 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	cat_index;

	dest_len = 0;
	src_len = 0;
	cat_index = 0;
	if ((dest == (void *)0 || src == (void *)0) && size == 0)
		return (0);
	while (src[src_len] != '\0')
		src_len++;
	while (dest[dest_len] != '\0')
	{
		if (dest_len >= size)
			return (size + src_len);
		dest_len++;
	}
	while (dest_len + cat_index + 1 < size && src[cat_index] != '\0')
	{
		dest[dest_len + cat_index] = src[cat_index];
		cat_index++;
	}
	dest[dest_len + cat_index] = '\0';
	return (src_len + dest_len);
}
