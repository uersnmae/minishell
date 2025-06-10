/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:56:30 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/30 19:22:25 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	len1 = ft_strlen(s1);
	const size_t	len2 = ft_strlen(s2);
	char			*res;
	char			*p;

	res = malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	p = res;
	ft_memcpy(p, s1, len1);
	ft_memcpy(p + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}
