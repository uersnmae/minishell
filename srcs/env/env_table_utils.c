/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:11:47 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 16:42:08 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_table.h"
#include "libft.h"

unsigned long	hash_string(const char *str)
{
	unsigned long	hash;

	hash = 5381;
	while (*str)
	{
		hash = ((hash << 5) + hash) + (unsigned char)*str;
		str++;
	}
	return (hash);
}

t_env_pair	*new_pair(const char *key, const char *value)
{
	t_env_pair	*pair;

	pair = malloc(sizeof(t_env_pair));
	if (!pair)
		return (NULL);
	pair->key = ft_strdup(key);
	if (value)
		pair->value = ft_strdup(value);
	else
		pair->value = NULL;
	pair->next = NULL;
	return (pair);
}
