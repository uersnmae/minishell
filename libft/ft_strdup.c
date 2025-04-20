/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:30:09 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/03 23:38:04 by kim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	src_len;
	char	*return_str;
	char	*psrc;

	psrc = (char *)src;
	src_len = ft_strlen(src);
	return_str = (char *)ft_calloc(src_len + 1, sizeof(char));
	if (return_str == NULL)
		return (NULL);
	ft_strlcpy(return_str, psrc, src_len + 1);
	return (return_str);
}
