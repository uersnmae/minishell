/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:18:50 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/07 16:27:54 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while ((s1[index] != '\0' && s2[index] != '\0') && index + 1 < n)
	{
		if (s1[index] != s2[index])
			break ;
		index++;
	}
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
