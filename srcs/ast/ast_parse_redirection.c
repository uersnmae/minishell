/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:54:28 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 20:55:15 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

int	is_redirection_token(t_toktype type)
{
	return (type == TK_REDIR_IN || type == TK_REDIR_OUT \
		|| type == TK_HEREDOC || type == TK_REDIR_APP);
}

static t_node_type	get_redir_node_type(t_toktype token)
{
	if (token == TK_REDIR_IN)
		return (NODE_TYPE_REDIR_IN);
	if (token == TK_REDIR_OUT)
		return (NODE_TYPE_REDIR_OUT);
	if (token == TK_HEREDOC)
		return (NODE_TYPE_HEREDOC);
	return (NODE_TYPE_REDIR_APPEND);
}

t_ast_node	*ast_parse_redirection(t_token **token, t_ast_node *left)
{
	t_token		*redir_token;
	t_token		*filename;
	t_ast_node	*right;
	t_ast_node	*node;
	t_node_type	type;

	while (*token && is_redirection_token((*token)->type))
	{
		redir_token = *token;
		*token = (*token)->next;
		if (*token == NULL || (*token)->type != TK_WORD)
			return (ast_handle_syntax_error(left, redir_token,
					(*token) == NULL));
		filename = *token;
		*token = filename->next;
		filename->next = NULL;
		right = ast_new_leaf_node(filename, NODE_TYPE_COMMAND);
		type = get_redir_node_type(redir_token->type);
		free(redir_token->value);
		free(redir_token);
		node = ast_new_binary_node(left, right, type);
		left = node;
	}
	return (left);
}
