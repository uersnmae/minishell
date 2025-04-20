/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:50:02 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/04 12:53:30 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char const *set, char c)
{
	char	*pset;

	pset = (char *)set;
	while (*pset)
	{
		if (*pset == c)
			return (1);
		pset++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ps1;
	char	*rps1;
	char	*trim;
	size_t	cpylen;

	if (s1 == NULL || set == NULL)
		return (NULL);
	ps1 = (char *)s1;
	rps1 = (char *)s1;
	while (*rps1)
		rps1++;
	while ((ft_check_set(set, *ps1)))
		ps1++;
	cpylen = ft_strlen(ps1);
	while (rps1 > ps1 && cpylen > 0 && (ft_check_set(set, *(--rps1))))
		cpylen--;
	trim = (char *)ft_calloc(cpylen + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, ps1, cpylen + 1);
	return (trim);
}
