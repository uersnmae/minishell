/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:55:06 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/07 14:10:44 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

t_ast_node	*ast_parse_subshell(t_token **token)
{
	t_ast_node	*node;
	t_token		*subs_token;

	if (*token == NULL || (*token)->type != TK_SUBSHELL)
		return (NULL);
	subs_token = *token;
	*token = subs_token->next;
	subs_token->next = NULL;
	node = ast_new_leaf_node(subs_token, NODE_TYPE_SUBSHELL);
	return (node);
}
