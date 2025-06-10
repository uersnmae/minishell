/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 22:22:21 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 15:38:57 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "exec.h"
#include "command_structs.h"

int	count_cmds(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	create_pipes(int *pipes, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipes + 2 * i) < 0)
		{
			while (i-- > 0)
			{
				close(pipes[2 * i]);
				close(pipes[2 * i + 1]);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

int	prepare_heredoc_redir(t_redir *r, t_shell *shell)
{
	char	*raw;
	pid_t	pid;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) < 0)
		return (-1);
	raw = ft_strdup(r->target);
	if (raw == NULL)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		exec_heredoc_child(raw, pipefd, shell);
	free(raw);
	waitpid(pid, &status, 0);
	close(pipefd[1]);
	if (WIFSIGNALED(status)
		|| (WIFEXITED((status)) && WEXITSTATUS(status) != 0))
		return (-1);
	r->fd = pipefd[0];
	return (0);
}

void	close_parent_heredoc_fds(t_job *jobs)
{
	t_job		*j;
	t_command	*c;
	t_redir		*r;

	j = jobs;
	while (j)
	{
		c = j->pipeline;
		while (c)
		{
			r = c->redirs;
			while (r)
			{
				if (r->type == HEREDOC && r->fd >= 0)
				{
					close(r->fd);
					r->fd = -1;
				}
				r = r->next;
			}
			c = c->next;
		}
		j = j->next;
	}
}

int	prepare_job_heredocs(t_job *job, t_shell *shell)
{
	t_command	*cmd;
	t_redir		*r;

	cmd = job->pipeline;
	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == HEREDOC)
				if (prepare_heredoc_redir(r, shell) < 0)
					return (-1);
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
