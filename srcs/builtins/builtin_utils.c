/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:12:53 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 16:30:29 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "command_structs.h"
#include "libft.h"
#include "env_table.h"
#include "builtins.h"
#include "minishell.h"

char	**parse_path(char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**paths;

	path_env = (char *)env_get(shell->env, "PATH");
	if (!path_env && ft_strchr(cmd, '\\') != NULL)
	{
		ft_putendl_fd("minishell: path_env error", STDERR_FILENO);
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		ft_putendl_fd("minishell: ft_split error", STDERR_FILENO);
		return (NULL);
	}
	return (paths);
}

char	**tokens_to_argv(t_token *tok)
{
	size_t	argc;
	t_token	*cur;
	char	**argv;
	size_t	i;

	argc = 0;
	cur = tok;
	while (cur && cur->type == TK_WORD)
	{
		argc++;
		cur = cur->next;
	}
	argv = malloc((argc + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	cur = tok;
	while (i < argc)
	{
		argv[i++] = ft_strdup(cur->value);
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

char	*join_path(const char *dir, const char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

char	*find_executable(const char *cmd, char **paths)
{
	char	*check_cmd;
	size_t	i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (paths && paths[i])
	{
		check_cmd = join_path(paths[i], cmd);
		if (check_cmd && access(check_cmd, X_OK) == 0)
			return (check_cmd);
		free(check_cmd);
		i++;
	}
	return (NULL);
}

void	free_path(char **paths)
{
	size_t	i;

	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
