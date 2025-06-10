/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:31:09 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 01:16:25 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "ast.h"
#include "minishell.h"
#include "signal_handler.h"
#include "command_structs.h"
#include "command_utils.h"
#include "builtins.h"
#include "exec.h"
#include "exec_utils.h"

static int	wait_pipeline(pid_t	*pids, int n, t_shell *shell)
{
	int	status;
	int	last;
	int	i;

	set_parent_signal();
	i = 0;
	last = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last = 128 + WTERMSIG(status);
		i++;
	}
	free(pids);
	if (WTERMSIG(status) == SIGQUIT && !shell->subshell_flag)
		ft_putendl_fd("Quit (Core dumped)", STDERR_FILENO);
	else if (WTERMSIG(status) == SIGINT && !shell->subshell_flag)
		ft_putendl_fd("", STDERR_FILENO);
	return (last);
}

static int	run_commands(t_command *cmds, t_shell *shell)
{
	int		n;
	pid_t	*pids;

	cmds->argv = build_argv_from_tokens(cmds->command_tokens, shell);
	if (!cmds->next && cmds->argv && is_builtin(cmds->argv[0]) \
		&& cmds->command_tokens->type != TK_SUBSHELL)
	{
		if (!apply_redirections(cmds, shell))
		{
			dup2(shell->stdin, STDIN_FILENO);
			dup2(shell->stdout, STDOUT_FILENO);
			return (shell->last_status);
		}
		shell->last_status = exec_builtin(cmds->argv, shell);
		dup2(shell->stdin, STDIN_FILENO);
		dup2(shell->stdout, STDOUT_FILENO);
		return (shell->last_status);
	}
	pids = spawn_pipeline(cmds, &n, shell);
	if (!pids)
		return (-1);
	shell->last_status = wait_pipeline(pids, n, shell);
	return (shell->last_status);
}

int	run_jobs(t_job *jobs, t_shell *shell)
{
	int	status;

	status = 0;
	while (jobs)
	{
		if ((jobs->conn == CONN_AND && status != 0)
			|| (jobs->conn == CONN_OR && status == 0))
		{
			jobs = jobs->next;
			continue ;
		}
		status = run_commands(jobs->pipeline, shell);
		jobs = jobs->next;
	}
	return (status);
}
