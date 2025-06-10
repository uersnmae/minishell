/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:39:56 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 15:49:10 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "minishell.h"
#include "ast.h"
#include "exec.h"
#include "builtins.h"
#include "env_table.h"

void	cleanup(char **path, t_shell *shell)
{
	if (shell->root_node)
		free_ast_node(shell->root_node);
	if (shell->env)
		env_table_free(shell->env);
	if (shell->base_dir)
		free(shell->base_dir);
	if (path)
		free_path(path);
	if (shell->line)
		free(shell->line);
	if (shell->envp)
		free_path(shell->envp);
	if (shell->jobs)
		free_job_list(shell->jobs);
	rl_clear_history();
	close(shell->stdin);
	close(shell->stdout);
}

int	error_status(char *msg, char *detail, int err_val, bool flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (flag)
		free(msg);
	ft_putchar_fd(' ', STDERR_FILENO);
	if (detail != NULL)
		ft_putendl_fd(detail, STDERR_FILENO);
	return (err_val);
}
