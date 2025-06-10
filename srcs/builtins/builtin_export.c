/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:26:46 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 18:50:54 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "builtins.h"
#include "minishell.h"

static int	is_valid_identifier(char *key)
{
	size_t	i;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static t_env_pair	*find_next_pair(t_env_table *env, char *last)
{
	size_t			i;
	t_env_pair		*cur;
	t_env_pair		*cand;

	cand = NULL;
	i = 0;
	while (i < env->bucket_count)
	{
		cur = env->buckets[i];
		while (cur)
		{
			if (ft_strncmp(cur->key, last, ft_strlen(cur->key)) > 0
				&& (!cand \
				|| ft_strncmp(cur->key, cand->key, ft_strlen(cur->key)) < 0))
				cand = cur;
			cur = cur->next;
		}
		i++;
	}
	return (cand);
}

static void	print_sorted_env(t_env_table *env)
{
	char			*last;
	t_env_pair		*next;

	last = "";
	next = find_next_pair(env, last);
	while (next != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, next->key, ft_strlen(next->key));
		if (next->value && *next->value)
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, next->value, ft_strlen(next->value));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		last = next->key;
		next = find_next_pair(env, last);
	}
}

static int	handle_arg(t_shell *shell, char *arg)
{
	char	*equal;
	char	*key;
	char	*val;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_strndup(arg, equal - arg);
		val = equal + 1;
	}
	else
	{
		key = ft_strdup(arg);
		if (env_get(shell->env, key))
		{
			free(key);
			return (0);
		}
		val = NULL;
	}
	if (!key)
		return (1);
	env_set(shell->env, key, val);
	free(key);
	return (0);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int		i;
	int		ret;

	if (argv[1] == NULL)
	{
		print_sorted_env(shell->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		if (handle_arg(shell, argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
