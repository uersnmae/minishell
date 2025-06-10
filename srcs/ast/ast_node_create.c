/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:54:37 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/30 20:54:37 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"

t_ast_node	*ast_new_leaf_node(t_token *token_list, t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->token_list = token_list;
	return (node);
}
