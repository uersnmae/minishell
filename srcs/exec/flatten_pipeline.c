/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:06:05 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 12:29:48 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command_structs.h"
#include "command_utils.h"
#include "exec.h"
#include "minishell.h"

static t_command	*create_command_from_node(t_ast_node *node, t_shell *shell)
{
	t_command	*cmd;

	(void)shell;
	cmd = ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->command_tokens = node->token_list;
	cmd->redirs = build_redirs_from_ast(node);
	cmd->next = NULL;
	if (cmd->command_tokens == NULL && cmd->redirs == NULL)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_command	*merge_pipelines(t_command *left, t_command *right)
{
	t_command	*cur;

	if (left == NULL)
		return (right);
	cur = left;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = right;
	return (left);
}

static t_command	*redirect_node(t_ast_node *node, t_shell *shell)
{
	t_command	*cmd;
	t_redir		*r;
	t_redir		*cur;

	cmd = flatten_pipeline(node->left, shell);
	r = build_redirs_from_ast(node);
	if (cmd == NULL && r != NULL)
	{
		free_command_list(cmd);
		free_redir_list(r);
		return (create_command_from_node(node, shell));
	}
	if (cmd == NULL || r == NULL)
		return (cmd);
	if (!cmd->redirs)
		cmd->redirs = r;
	else
	{
		cur = cmd->redirs;
		while (cur->next)
			cur = cur->next;
		cur->next = r;
	}
	return (cmd);
}

t_command	*flatten_pipeline(t_ast_node *node, t_shell *shell)
{
	t_command	*left;
	t_command	*right;

	if (node == NULL)
		return (NULL);
	if (is_redir_node(node))
		return (redirect_node(node, shell));
	if (node->type == NODE_TYPE_PIPE)
	{
		left = flatten_pipeline(node->left, shell);
		right = flatten_pipeline(node->right, shell);
		return (merge_pipelines(left, right));
	}
	return (create_command_from_node(node, shell));
}
