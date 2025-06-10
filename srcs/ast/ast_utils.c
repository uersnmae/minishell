/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:55:17 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/28 21:55:41 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "tokenizer.h"
#include "ast.h"
#include "libft.h"

t_ast_node	*ast_handle_syntax_error(t_ast_node *left, t_token *op_tok,
				bool flag)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
			STDERR_FILENO);
	ft_putstr_fd(op_tok->value, STDERR_FILENO);
	ft_putendl_fd("`", STDERR_FILENO);
	if (flag)
		free_tokens(&op_tok);
	if (left)
		free(left);
	return (NULL);
}

void	free_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast_node(node->left);
	if (node->right)
		free_ast_node(node->right);
	if (node->token_list)
		free_tokens(&node->token_list);
	free(node);
}

int	is_valid_cmd_token(t_token *tok)
{
	return (tok && (tok->type == TK_WORD || tok->type == TK_SUBSHELL));
}
