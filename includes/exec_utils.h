/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:36:04 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 10:11:57 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "command_structs.h"
# include "minishell.h"

int		count_cmds(t_command *cmd);
int		create_pipes(int *pipes, int n);
void	close_pipes(int *pipes, int n);
int		prepare_heredoc_redir(t_redir *r, t_shell *shell);
int		prepare_job_heredocs(t_job *job, t_shell *shell);

char	*handle_redirect_pattern(char *token, t_shell *shell);

pid_t	*spawn_pipeline(t_command *cmds, int *n_cmds, t_shell *shell);
int		alloc_resources(int n, pid_t **pids, int **pipes);

#endif
