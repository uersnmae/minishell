/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirs_from_ast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:14:18 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 15:55:12 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"
#include "command_structs.h"
#include "ast.h"

bool	is_redir_node(const t_ast_node *node)
{
	return (node->type == NODE_TYPE_REDIR_IN
		|| node->type == NODE_TYPE_REDIR_OUT
		|| node->type == NODE_TYPE_REDIR_APPEND
		|| node->type == NODE_TYPE_HEREDOC);
}

static t_redir_type	map_redir_type(const t_ast_node *node)
{
	if (node->type == NODE_TYPE_REDIR_IN)
		return (REDIR_IN);
	if (node->type == NODE_TYPE_REDIR_OUT)
		return (REDIR_OUT);
	if (node->type == NODE_TYPE_REDIR_APPEND)
		return (REDIR_APPEND);
	return (HEREDOC);
}

static t_redir	*merge_redir_lists(t_redir *left, t_redir *right)
{
	t_redir	*cur;

	if (left == NULL)
		return (right);
	cur = left;
	while (cur->next)
		cur = cur->next;
	cur->next = right;
	return (left);
}

static t_redir	*create_redir_node(const t_ast_node *node)
{
	t_redir	*r;

	r = ft_calloc(1, sizeof(*r));
	if (r == NULL)
		return (NULL);
	r->type = map_redir_type(node);
	r->target = ft_strdup(node->right->token_list->value);
	if (r->target == NULL)
	{
		free(r);
		return (NULL);
	}
	r->fd = -1;
	r->next = NULL;
	return (r);
}

t_redir	*build_redirs_from_ast(t_ast_node *node)
{
	t_redir	*left;
	t_redir	*right;

	if (node == NULL)
		return (NULL);
	if (is_redir_node((node)))
		return (create_redir_node(node));
	left = build_redirs_from_ast(node->left);
	right = build_redirs_from_ast(node->right);
	return (merge_redir_lists(left, right));
}
