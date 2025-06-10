/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:04:40 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/23 15:47:31 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>

# include "command_structs.h"
# include "minishell.h"

typedef struct s_exec_ctx
{
	int		cmd_count;
	int		*pipes;
	pid_t	*pids;
	char	**paths;
	t_shell	*shell;
}	t_exec_ctx;

bool	apply_redirections(t_command *cmd, t_shell *shell);
void	setup_io_and_close(int i, const t_exec_ctx *ctx);
void	clean_exit(const t_exec_ctx *ctx, int status, bool do_cleanup);

int		run_jobs(t_job *jobs, t_shell *shell);
void	close_parent_heredoc_fds(t_job *jobs);

void	exec_heredoc_child(char *raw_delim, int pipefd[2], t_shell *shell);
void	exec_subshell(t_command *command, t_shell *shell);

void	free_redir_list(t_redir *redir);
void	free_command_list(t_command *cmd);
void	free_job_list(t_job *jobs);

#endif
