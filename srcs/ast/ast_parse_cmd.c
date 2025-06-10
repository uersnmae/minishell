/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:54:49 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 12:31:07 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

static t_ast_node	*attach_subtree_for_prefix(
	t_ast_node *redir_tree, t_ast_node *cmd_node)
{
	t_ast_node	*curr;

	curr = redir_tree;
	while (curr->left)
		curr = curr->left;
	curr->left = cmd_node;
	return (redir_tree);
}

static t_token	*detach_simple_command(t_token **token)
{
	t_token	*start;
	t_token	*end;
	t_token	*prev;

	start = *token;
	end = start;
	prev = NULL;
	while (end && end->type == TK_WORD)
	{
		prev = end;
		end = end->next;
	}
	if (prev)
		prev->next = NULL;
	*token = end;
	return (start);
}

t_ast_node	*ast_parse_cmd(t_token **token)
{
	t_ast_node	*prefix_tree;
	t_ast_node	*cmd_node;

	prefix_tree = NULL;
	cmd_node = NULL;
	prefix_tree = ast_parse_redirection(token, NULL);
	if (*token && (*token)->type == TK_SUBSHELL)
	{
		cmd_node = ast_parse_subshell(token);
		if (cmd_node == NULL)
			return (NULL);
		return (ast_parse_redirection(token, cmd_node));
	}
	if (!*token || (*token)->type != TK_WORD)
		return (prefix_tree);
	cmd_node = ast_new_leaf_node(detach_simple_command(token),
			NODE_TYPE_COMMAND);
	if (cmd_node == NULL)
		return (NULL);
	if (prefix_tree)
		prefix_tree = attach_subtree_for_prefix(prefix_tree, cmd_node);
	else
		prefix_tree = cmd_node;
	return (ast_parse_redirection(token, prefix_tree));
}
