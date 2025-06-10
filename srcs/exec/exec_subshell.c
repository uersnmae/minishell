/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:36:36 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 14:50:21 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ast.h"
#include "env_table.h"
#include "exec.h"
#include "builtins.h"
#include "command_structs.h"
#include "minishell.h"

extern char	**environ;

static void	init_subshell(
	char *argv[4], char **minishell_path, char ***envp, t_shell *shell)
{
	*minishell_path = ft_strjoin(shell->base_dir, "/minishell_bonus");
	argv[0] = *minishell_path;
	argv[1] = "-c";
	argv[2] = shell->curr_node->token_list->value;
	argv[3] = NULL;
	*envp = env_to_envp(shell->env);
}

void	exec_subshell(t_command *command, t_shell *shell)
{
	char	*argv[4];
	char	**envp;
	char	*minishell_path;

	shell->curr_node->token_list = command->command_tokens;
	init_subshell(argv, &minishell_path, &envp, shell);
	execve(minishell_path, argv, envp);
	free(minishell_path);
	free_path(envp);
	perror("subshell");
	exit(127);
}
