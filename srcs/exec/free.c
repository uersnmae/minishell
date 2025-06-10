/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:05:14 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 12:26:43 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "command_structs.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		free(redir->target);
		next = redir->next;
		free(redir);
		redir = next;
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*next;
	int			i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		if (cmd->redirs)
			free_redir_list(cmd->redirs);
		free(cmd);
		cmd = next;
	}
}

void	free_job_list(t_job *jobs)
{
	t_job	*next;

	while (jobs)
	{
		next = jobs->next;
		if (jobs->pipeline)
			free_command_list(jobs->pipeline);
		free(jobs);
		jobs = next;
	}
}
