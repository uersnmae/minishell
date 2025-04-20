/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:07:31 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/03 23:21:03 by kim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ps;
	int		index;
	int		jndex;

	ps = (char *)s;
	index = 0;
	jndex = -1;
	while (ps[index] != '\0')
	{
		if (ps[index] == (char)c)
			jndex = index;
		index++;
	}
	if (ps[index] == (char)c)
		jndex = index;
	if (jndex != -1)
		return (ps + jndex);
	return (0);
}
