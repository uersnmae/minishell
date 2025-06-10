/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:11:25 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 17:10:52 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_table.h"

const char	*env_get(t_env_table *env, const char *key)
{
	unsigned long	i;
	t_env_pair		*cur;

	if (!env || !key)
		return (NULL);
	i = hash_string(key) % env->bucket_count;
	cur = env->buckets[i];
	while (cur)
	{
		if (!ft_strncmp(cur->key, (char *)key, (ft_strlen(key))))
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

void	env_set(t_env_table *env, const char *key, const char *value)
{
	unsigned long	i;
	t_env_pair		*cur;

	i = hash_string(key) % env->bucket_count;
	cur = env->buckets[i];
	while (cur)
	{
		if (!ft_strncmp(cur->key, (char *)key, (ft_strlen(key))))
		{
			free(cur->value);
			if (value)
				cur->value = ft_strdup(value);
			else if (value == NULL)
				cur->value = NULL;
			else
				cur->value = ft_strdup("");
			return ;
		}
		cur = cur->next;
	}
	cur = new_pair(key, value);
	cur->next = env->buckets[i];
	env->buckets[i] = cur;
}

void	env_unset(t_env_table *env, const char *key)
{
	unsigned long	i;
	t_env_pair		*cur;
	t_env_pair		*pair;

	i = hash_string(key) % env->bucket_count;
	cur = env->buckets[i];
	pair = NULL;
	while (cur)
	{
		if (!ft_strncmp(cur->key, (char *)key, (ft_strlen(key))))
		{
			if (pair)
				pair->next = cur->next;
			else
				env->buckets[i] = cur->next;
			free(cur->key);
			free(cur->value);
			return (free(cur));
		}
		pair = cur;
		cur = cur->next;
	}
}

void	env_table_free(t_env_table *env)
{
	size_t		i;
	t_env_pair	*cur;
	t_env_pair	*next;

	if (env == NULL)
		return ;
	i = 0;
	while (i < env->bucket_count)
	{
		cur = env->buckets[i];
		while (cur != NULL)
		{
			next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			cur = next;
		}
		i++;
	}
	free(env->buckets);
	free(env);
}
