/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:41:54 by kim               #+#    #+#             */
/*   Updated: 2025/05/27 01:03:06 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "ast.h"
#include "env_table.h"
#include "tokenizer.h"
#include "minishell.h"

extern char	**environ;

static char	**copy_environ(void)
{
	char	**envp;
	size_t	count;
	size_t	i;

	count = 0;
	while (environ[count])
		count++;
	envp = malloc(sizeof(char *) * (count + 1));
	if (envp == NULL || count == 0)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envp[i] = ft_strdup(environ[i]);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static void	init_minishell(int argc, char **envp, t_shell *shell)
{
	shell->root_node = NULL;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->env = env_init(envp);
	shell->envp = envp;
	shell->last_status = 0;
	shell->base_dir = ft_strdup(env_get(shell->env, "PWD"));
	shell->stdin = dup(STDIN_FILENO);
	shell->stdout = dup(STDOUT_FILENO);
	shell->running = 1;
	shell->subshell_flag = 0;
	if (argc != 1)
		shell->subshell_flag = 1;
}

static int	run_subshell(char *argv, t_shell *shell)
{
	if (!tokenize(argv, &shell->tokens))
		return (1);
	shell->root_node = ast_create(&shell->tokens);
	if (shell->root_node == NULL)
		return (1);
	shell->curr_node = shell->root_node;
	run_ast(shell);
	free(shell->base_dir);
	return (shell->last_status);
}

int	main(int argc, char **argv)
{
	char	**envp;
	t_shell	shell;

	envp = copy_environ();
	if (envp == NULL)
		return (EXIT_FAILURE);
	init_minishell(argc, envp, &shell);
	if (argc == 1)
	{
		shell.last_status = run_cmd_line(&shell);
		env_free_envp(envp);
		exit(shell.last_status);
	}
	else if (argc == 3 && !ft_strncmp(argv[1], "-c", ft_strlen(argv[1]) + 1))
	{
		shell.last_status = run_subshell(argv[2], &shell);
		env_free_envp(envp);
		exit(shell.last_status);
	}
	else
		exit(EXIT_FAILURE);
}
