/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:54:59 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/28 21:48:27 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

t_ast_node	*ast_parse_pipe(t_token	**token)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*node;
	t_token		*op;

	left = ast_parse_cmd(token);
	if (left == NULL)
		return (NULL);
	while (*token && (*token)->type == TK_PIPE)
	{
		op = *token;
		*token = (*token)->next;
		if (!is_valid_cmd_token(*token))
			return (ast_handle_syntax_error(left, op, true));
		right = ast_parse_cmd(token);
		if (right == NULL)
			return (ast_handle_syntax_error(left, op, true));
		free(op->value);
		free(op);
		node = ast_new_binary_node(left, right, NODE_TYPE_PIPE);
		if (node == NULL)
			return (NULL);
		left = node;
	}
	return (left);
}
