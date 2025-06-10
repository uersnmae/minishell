/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:49:38 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 15:54:50 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "exec.h"
#include "exec_utils.h"
#include "command_structs.h"
#include "command_utils.h"
#include "signal_handler.h"
#include "minishell.h"

int	run_ast(t_shell *shell)
{
	t_job	*jobs;
	int		status;

	set_parent_signal();
	jobs = flatten_jobs(shell->root_node, shell);
	if (!jobs)
		return (shell->last_status);
	shell->jobs = jobs;
	if (prepare_job_heredocs(jobs, shell) < 0)
	{
		free_job_list(jobs);
		shell->last_status = 130;
		return (shell->last_status);
	}
	status = run_jobs(jobs, shell);
	close_parent_heredoc_fds(jobs);
	free_job_list(jobs);
	shell->last_status = status;
	return (shell->last_status);
}
