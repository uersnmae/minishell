/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:12:20 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 17:29:16 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_table.h"

static void	add_envp(t_env_table *env, char **envp)
{
	size_t	i;
	char	*equal;

	i = 0;
	while (envp && envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			*equal = '\0';
			env_set(env, envp[i], equal + 1);
			*equal = '=';
		}
		i++;
	}
}

static size_t	count_all(t_env_table *env)
{
	size_t		i;
	size_t		total;
	t_env_pair	*cur;

	total = 0;
	i = 0;
	while (i < env->bucket_count)
	{
		cur = env->buckets[i];
		while (cur)
		{
			if (cur->value)
				total++;
			cur = cur->next;
		}
		i++;
	}
	return (total);
}

t_env_table	*env_table_create(size_t buckets, char **envp)
{
	t_env_table	*env;

	env = malloc(sizeof(t_env_table));
	if (!env)
		return (NULL);
	env->buckets = ft_calloc(buckets, sizeof(t_env_pair *));
	if (!env->buckets)
		return (free(env), NULL);
	env->bucket_count = buckets;
	add_envp(env, envp);
	return (env);
}

static char	*env_pair_to_string(t_env_pair *cur)
{
	char	*temp;
	char	*result;

	if (!cur->value)
		return (NULL);
	temp = ft_strjoin(cur->key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, cur->value);
	free(temp);
	return (result);
}

char	**env_to_envp(t_env_table *env)
{
	size_t		i;
	size_t		j;
	char		**envp_arr;
	t_env_pair	*cur;

	envp_arr = malloc(sizeof(char *) * (count_all(env) + 1));
	if (!envp_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env->bucket_count)
	{
		cur = env->buckets[i++];
		while (cur)
		{
			if (cur->value)
				envp_arr[j++] = env_pair_to_string(cur);
			cur = cur->next;
		}
	}
	envp_arr[j] = NULL;
	return (envp_arr);
}
