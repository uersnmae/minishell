/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:05:03 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/28 17:27:14 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

static t_ast_node	*ast_parse_and_if(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*op_tok;

	left = ast_parse_pipe(token);
	if (left == NULL)
		return (NULL);
	while (*token && (*token)->type == TK_AND_IF)
	{
		op_tok = *token;
		*token = (*token)->next;
		if (!is_valid_cmd_token(*token))
			return (ast_handle_syntax_error(left, op_tok, true));
		op_tok->next = NULL;
		right = ast_parse_pipe(token);
		if (right == NULL)
			return (ast_handle_syntax_error(left, op_tok, true));
		left = ast_new_binary_node(left, right, NODE_TYPE_AND_IF);
		left->token_list = op_tok;
	}
	return (left);
}

t_ast_node	*ast_parse_and_or(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*op_tok;

	left = ast_parse_and_if(token);
	if (left == NULL)
		return (NULL);
	while (*token && (*token)->type == TK_OR_IF)
	{
		op_tok = *token;
		*token = (*token)->next;
		if (!is_valid_cmd_token(*token))
			return (ast_handle_syntax_error(left, op_tok, true));
		op_tok->next = NULL;
		right = ast_parse_and_if(token);
		if (right == NULL)
			return (ast_handle_syntax_error(left, op_tok, true));
		left = ast_new_binary_node(left, right, NODE_TYPE_OR_IF);
		left->token_list = op_tok;
	}
	return (left);
}
