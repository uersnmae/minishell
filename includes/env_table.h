/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:02:29 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 17:29:20 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TABLE_H
# define ENV_TABLE_H

# include <stddef.h>
# include <stdlib.h>

# include "libft.h"

typedef struct s_env_pair
{
	char				*key;
	char				*value;
	struct s_env_pair	*next;
}	t_env_pair;

typedef struct s_env_table
{
	t_env_pair			**buckets;
	size_t				bucket_count;
}	t_env_table;

char			**env_to_envp(t_env_table *env);
t_env_table		*env_table_create(size_t buckets, char **envp);

const char		*env_get(t_env_table *env, const char *key);
void			env_set(t_env_table *env, const char *key, const char *value);
void			env_unset(t_env_table *env, const char *key);
void			env_table_free(t_env_table *env);

unsigned long	hash_string(const char *str);
t_env_pair		*new_pair(const char *key, const char *value);

t_env_table		*env_init(char **envp);
void			env_free_envp(char **envp);

#endif
