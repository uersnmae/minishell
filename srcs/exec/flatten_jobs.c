/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:59:35 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 15:56:19 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_structs.h"
#include "command_utils.h"

static t_job	*create_job_from_node(t_ast_node *node, t_shell *shell)
{
	t_job	*job;

	job = ft_calloc(1, sizeof(*job));
	if (job == NULL)
		return (NULL);
	job->conn = CONN_NONE;
	job->pipeline = flatten_pipeline(node, shell);
	job->next = NULL;
	if (!job->pipeline)
	{
		free(job);
		return (NULL);
	}
	return (job);
}

static t_job	*merge_jobs(t_job *left, t_job *right, t_connector conn)
{
	t_job	*last;

	if (left == NULL)
	{
		if (right != NULL)
			right->conn = conn;
		return (right);
	}
	last = left;
	while (last->next)
		last = last->next;
	if (right != NULL)
		right->conn = conn;
	last->next = right;
	return (left);
}

t_job	*flatten_jobs(t_ast_node *root, t_shell *shell)
{
	t_job	*left;
	t_job	*right;

	if (root == NULL)
		return (NULL);
	if (root->type == NODE_TYPE_AND_IF || root->type == NODE_TYPE_OR_IF)
	{
		left = flatten_jobs(root->left, shell);
		right = flatten_jobs(root->right, shell);
		if (root->type == NODE_TYPE_AND_IF)
			return (merge_jobs(left, right, CONN_AND));
		else
			return (merge_jobs(left, right, CONN_OR));
	}
	return (create_job_from_node(root, shell));
}
