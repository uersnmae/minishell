/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_pipeline_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:48:01 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/23 15:50:20 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "exec.h"
#include "builtins.h"
#include "exec_utils.h"

void	setup_io_and_close(int i, const t_exec_ctx *ctx)
{
	int	j;

	if (i > 0)
		dup2(ctx->pipes[2 * (i - 1)], STDIN_FILENO);
	if (i < ctx->cmd_count - 1)
		dup2(ctx->pipes[2 * i + 1], STDOUT_FILENO);
	j = 0;
	while (ctx->pipes && j < 2 * (ctx->cmd_count - 1))
		close(ctx->pipes[j++]);
}

int	alloc_resources(int n, pid_t **pids, int **pipes)
{
	*pids = malloc(sizeof(pid_t) * n);
	if (!*pids)
		return (-1);
	if (n > 1)
	{
		*pipes = malloc(sizeof(int) * 2 * (n - 1));
		if (!*pipes)
		{
			free(*pids);
			return (-1);
		}
	}
	else
		*pipes = NULL;
	return (0);
}

void	clean_exit(const t_exec_ctx *ctx, int status, bool do_cleanup)
{
	free(ctx->pids);
	if (ctx->paths)
		free_path(ctx->paths);
	if (do_cleanup)
		cleanup(NULL, ctx->shell);
	exit(status);
}
