/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 03:18:02 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/28 17:22:13 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokenizer.h"

typedef enum e_node_type
{
	NODE_TYPE_COMMAND,
	NODE_TYPE_PIPE,
	NODE_TYPE_REDIR_IN,
	NODE_TYPE_REDIR_OUT,
	NODE_TYPE_REDIR_APPEND,
	NODE_TYPE_HEREDOC,
	NODE_TYPE_AND_IF,
	NODE_TYPE_OR_IF,
	NODE_TYPE_SUBSHELL
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_token				*token_list;
}	t_ast_node;

t_ast_node	*ast_new_leaf_node(t_token *token_list, t_node_type type);

t_ast_node	*ast_create(t_token **tokens);
t_ast_node	*ast_parse_cmd(t_token **token);
t_ast_node	*ast_parse_pipe(t_token **token);
t_ast_node	*ast_parse_and_or(t_token **token);
t_ast_node	*ast_parse_redirection(t_token **token, t_ast_node *left);
t_ast_node	*ast_parse_subshell(t_token **token);

int			is_valid_cmd_token(t_token *tok);
int			is_redirection_token(t_toktype type);
t_ast_node	*ast_handle_syntax_error(t_ast_node *left, t_token *op_tok,
				bool flag);
t_ast_node	*ast_new_binary_node(t_ast_node *left, t_ast_node *right,
				t_node_type type);
void		free_ast_node(t_ast_node *node);

t_ast_node	*ast_parse_complete_command(t_token **token);

void		ast_print_tree(t_ast_node *node, int depth);

void		fail_ast_parse(t_token *tokens);

#endif
