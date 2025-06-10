/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:49:16 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 16:24:09 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "command_structs.h"
#include "command_utils.h"
#include "minishell.h"
#include "signal_handler.h"
#include "exec.h"
#include "exec_utils.h"
#include "builtins.h"
#include "tokenizer.h"

static void	exec_normal(t_command *cur, const t_exec_ctx *ctx)
{
	char	*full;
	char	**envp;

	if (cur->argv && is_builtin(cur->argv[0]))
		clean_exit(ctx, exec_builtin(cur->argv, ctx->shell), true);
	if (!cur->argv || !cur->argv[0])
		clean_exit(ctx, EXIT_SUCCESS, false);
	full = find_executable(cur->argv[0], ctx->paths);
	if (!full)
		clean_exit(
			ctx,
			error_status(
				ft_strdup(cur->argv[0]),
				"command not found",
				127, true),
			true);
	envp = env_to_envp(ctx->shell->env);
	execve(full, cur->argv, envp);
	env_free_envp(envp);
	free(full);
	clean_exit(ctx, EXIT_FAILURE, true);
}

static void	exec_child(t_command *cur, int i, const t_exec_ctx *ctx)
{
	set_child_signal();
	setup_io_and_close(i, ctx);
	free(ctx->pipes);
	if (!apply_redirections(cur, ctx->shell))
	{
		free(ctx->pids);
		if (ctx->paths)
			free_path(ctx->paths);
		cleanup(NULL, ctx->shell);
		exit(ctx->shell->last_status);
	}
	if (cur->command_tokens == NULL)
		clean_exit(ctx, ctx->shell->last_status, true);
	if (cur->argv == NULL)
		cur->argv = build_argv_from_tokens(cur->command_tokens, ctx->shell);
	if (cur->command_tokens->type == TK_SUBSHELL)
		exec_subshell(cur, ctx->shell);
	else
		exec_normal(cur, ctx);
}

static void	spawn_children(t_exec_ctx *ctx, pid_t *pids, t_command *cmds)
{
	t_command	*cur;
	int			i;

	i = -1;
	cur = cmds;
	while (++i < ctx->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(error_status("fork", NULL, EXIT_FAILURE, false));
		if (pids[i] == 0)
		{
			close(ctx->shell->stdout);
			close(ctx->shell->stdin);
			exec_child(cur, i, ctx);
		}
		cur = cur->next;
	}
	i = 0;
	if (ctx->pipes)
	{
		while (i < 2 * (ctx->cmd_count - 1))
			close(ctx->pipes[i++]);
	}
}

static bool	setup_pipes_and_paths(t_exec_ctx *ctx,
								int n_cmds,
								t_command *cmds,
								t_shell *shell)
{
	if (n_cmds > 1)
	{
		if (create_pipes(ctx->pipes, n_cmds) < 0)
		{
			free(ctx->pids);
			free(ctx->pipes);
			return (false);
		}
	}
	if (cmds->command_tokens == NULL && cmds->redirs != NULL)
		while (cmds && cmds->command_tokens == NULL)
			cmds = cmds->next;
	if (cmds == NULL)
	{
		ctx->paths = NULL;
		return (true);
	}
	ctx->paths = parse_path(cmds->command_tokens->value, shell);
	if (ctx->paths == NULL)
	{
		free(ctx->pids);
		free(ctx->pipes);
		return (false);
	}
	return (true);
}

pid_t	*spawn_pipeline(t_command *cmds, int *n_cmds, t_shell *shell)
{
	t_exec_ctx	ctx;
	bool		pure_redir;

	*n_cmds = count_cmds(cmds);
	if (*n_cmds < 0 || alloc_resources(*n_cmds, &ctx.pids, &ctx.pipes) < 0)
		return (NULL);
	pure_redir = (*n_cmds == 1 && cmds->command_tokens == NULL);
	if (pure_redir)
		ctx.paths = NULL;
	else if (!setup_pipes_and_paths(&ctx, *n_cmds, cmds, shell))
		return (NULL);
	ctx.shell = shell;
	ctx.cmd_count = *n_cmds;
	spawn_children(&ctx, ctx.pids, cmds);
	if (ctx.pipes)
		free(ctx.pipes);
	if (ctx.paths)
		free_path(ctx.paths);
	return (ctx.pids);
}
