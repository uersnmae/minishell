/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:54:54 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/28 17:19:40 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

t_ast_node	*ast_create(t_token **tokens)
{
	t_token	*op;

	if (*tokens && ((((*tokens)->type == TK_PIPE))
			|| (((*tokens)->type == TK_REDIR_APP) && (*tokens)->next == NULL)
			|| (((*tokens)->type == TK_REDIR_IN) && (*tokens)->next == NULL)
			|| (((*tokens)->type == TK_REDIR_OUT) && (*tokens)->next == NULL)
			|| (((*tokens)->type == TK_HEREDOC) && (*tokens)->next == NULL)
			|| (*tokens)->type == TK_AND_IF
			|| (*tokens)->type == TK_OR_IF))
	{
		op = *tokens;
		*tokens = op->next;
		return (ast_handle_syntax_error(NULL, op,
				((*tokens) != NULL) && ((op->type != TK_PIPE)
					&& (op->type != TK_OR_IF) && (op->type != TK_AND_IF))));
	}
	return (ast_parse_and_or(tokens));
}

t_ast_node	*ast_new_binary_node(t_ast_node *left,
								t_ast_node *right,
								t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->token_list = NULL;
	return (node);
}
