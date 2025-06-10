/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:22:32 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 22:37:26 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "expansion.h"
#include "libft.h"

char	*get_env_value(t_env_table *env, const char *key)
{
	const char	*value;

	value = env_get(env, key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*get_last_status(size_t *idx, t_shell *shell)
{
	*idx += 2;
	return (ft_itoa(shell->last_status));
}

char	*sub_var(const char *str, size_t *idx, t_shell *shell)
{
	size_t	i;
	char	*key;
	char	*val;
	char	*val_dup;

	if (str[1] == '?')
		return (get_last_status(idx, shell));
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	key = ft_substr(str + 1, 0, i - 1);
	if (key == NULL)
		exit(EXIT_FAILURE);
	*idx += i;
	val = get_env_value(shell->env, key);
	if (val == NULL)
		val_dup = ft_strdup("");
	else
	{
		val_dup = ft_strdup(val);
		free(val);
	}
	free(key);
	return (val_dup);
}
