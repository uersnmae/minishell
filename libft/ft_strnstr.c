/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:53:39 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/01 16:53:39 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char	*paddr;
	char	*str1;
	char	*str2;
	size_t	index;

	if ((str == (void *)0 || to_find == (void *)0) && len == 0)
		return (0);
	paddr = (char *)str;
	if (*to_find == '\0')
		return (paddr);
	while (*paddr && len-- > 0)
	{
		index = 0;
		str1 = paddr;
		str2 = (char *)to_find;
		while (*str1 && *str2 && (*str1 == *str2) && index++ <= len)
		{
			str1++;
			str2++;
		}
		if (*str2 == '\0')
			return (paddr);
		paddr++;
	}
	return (0);
}
