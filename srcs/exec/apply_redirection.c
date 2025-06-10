/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:53:06 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/29 09:26:32 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "exec.h"
#include "exec_utils.h"
#include "command_structs.h"
#include "minishell.h"

static int	get_fd(char *path, t_redir *r)
{
	int	fd;

	if (r->type == REDIR_IN)
		fd = open(path, O_RDONLY);
	else if (r->type == REDIR_OUT)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == REDIR_APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = r->fd;
	return (fd);
}

static void	close_fds(t_redir *r, t_redir *q)
{
	while (q != r)
	{
		if (q->fd >= 0)
			close(q->fd);
		q = q->next;
	}
}

static bool	prepare_redirections(t_command *cmd, t_shell *shell)
{
	t_redir	*r;
	t_redir	*q;
	char	*path;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		path = handle_redirect_pattern(r->target, shell);
		fd = get_fd(path, r);
		if (fd < 0)
		{
			shell->last_status = \
				error_status(strerror(errno), path, EXIT_FAILURE, false);
			free(path);
			q = cmd->redirs;
			close_fds(r, q);
			return (false);
		}
		free(path);
		r->fd = fd;
		r = r->next;
	}
	return (true);
}

bool	apply_redirections(t_command *cmd, t_shell *shell)
{
	t_redir	*r;

	if (!prepare_redirections(cmd, shell))
		return (false);
	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN || r->type == HEREDOC)
			dup2(r->fd, STDIN_FILENO);
		else
			dup2(r->fd, STDOUT_FILENO);
		if (r->fd >= 0)
			close(r->fd);
		r = r->next;
	}
	return (true);
}
