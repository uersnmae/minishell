/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:45:11 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/05 17:43:58 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_get_str_count(char const *str, char c)
{
	unsigned int	index;
	unsigned int	cnt;
	int				flag;

	index = 0;
	cnt = 0;
	flag = 0;
	if (str == NULL)
		return (cnt);
	while (str[index])
	{
		if (!(str[index] == c) && flag == 0)
		{
			flag = 1;
			cnt++;
		}
		else if (str[index] == c)
			flag = 0;
		index++;
	}
	return (cnt);
}

static char	*ft_add_words(char const *s, char c, unsigned int *index)
{
	unsigned int	len;
	char			*ret;

	len = 0;
	if (s == NULL)
		return (NULL);
	while (s[*index] == c && s[*index] != '\0')
		(*index)++;
	while (s[*index + len] != c && s[*index + len] != '\0')
		len++;
	ret = ft_substr(s, *index, len);
	if (ret == NULL)
		return (NULL);
	while (s[*index] != c && s[*index] != '\0')
		(*index)++;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	index;
	unsigned int	ret_index;
	unsigned int	ret_len;
	char			**ret;

	index = 0;
	ret_index = 0;
	ret_len = ft_get_str_count(s, c);
	ret = (char **)ft_calloc(ret_len + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (ret_index < ret_len)
	{
		ret[ret_index] = ft_add_words(s, c, &index);
		if (ret[ret_index++] == NULL)
		{
			while (--ret_index > 0)
				free(ret[ret_index]);
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}
