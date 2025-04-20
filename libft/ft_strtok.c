/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:21:03 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/05 21:08:28 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdelim(const char *delim, char c)
{
	unsigned int	delim_index;

	delim_index = 0;
	if (c == 0)
		return (1);
	while (delim[delim_index] != '\0')
	{
		if (c == delim[delim_index++])
			return (1);
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*static_str;
	char		*delim_start;

	if (str != (void *)0)
		static_str = str;
	else if (static_str == (void *)0)
		return ((void *)0);
	while (*static_str && ft_isdelim(delim, *static_str))
		static_str++;
	if (*static_str == '\0')
	{
		static_str = (void *)0;
		return ((void *)0);
	}
	delim_start = static_str;
	while (*static_str && !ft_isdelim(delim, *static_str))
		static_str++;
	if (*static_str != '\0')
	{
		*static_str = '\0';
		static_str++;
	}
	return (delim_start);
}
