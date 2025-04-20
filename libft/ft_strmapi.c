/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:28:08 by kim               #+#    #+#             */
/*   Updated: 2024/10/03 14:20:13 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ps;
	char	*ret;
	size_t	index;

	ps = (char *)s;
	if (s == NULL)
		return (NULL);
	ret = (char *)ft_calloc(sizeof(char), (ft_strlen(ps) + 1));
	if (ret == NULL)
		return (NULL);
	index = 0;
	while (*ps)
	{
		*(ret + index) = f(index, *(ps++));
		++index;
	}
	return (ret);
}
