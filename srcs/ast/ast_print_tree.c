/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:55:13 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/15 10:11:16 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "libft.h"

static void	print_indent(int depth);
static void	print_node_type(t_node_type type);
static void	print_node(char *node_type, char *node_value);
static void	print_subshell(t_ast_node *node, int depth);

static void	print_subshell(t_ast_node *node, int depth)
{
	t_token	*t;

	t = node->token_list;
	while (t)
	{
		print_indent(depth + 1);
		print_node("SUBSHELL_TOKEN: ", t->value);
		t = t->next;
	}
}

void	ast_print_tree(t_ast_node *node, int depth)
{
	t_token	*token;

	token = NULL;
	if (node == NULL)
		return ;
	print_indent(depth);
	print_node_type(node->type);
	if (node->type == NODE_TYPE_COMMAND)
	{
		token = node->token_list;
		while (token)
		{
			print_indent(depth + 1);
			print_node("WORD: ", token->value);
			token = token->next;
		}
	}
	else if (node->type == NODE_TYPE_SUBSHELL)
		print_subshell(node, depth);
	else
	{
		ast_print_tree(node->left, depth + 1);
		ast_print_tree(node->right, depth + 1);
	}
}

static void	print_indent(int depth)
{
	while (depth--)
		ft_putstr_fd("\t", STDOUT_FILENO);
}

static void	print_node_type(t_node_type type)
{
	const char	*types[] = {
	[NODE_TYPE_COMMAND] = "COMMAND",
	[NODE_TYPE_PIPE] = "PIPE",
	[NODE_TYPE_AND_IF] = "AND_IF",
	[NODE_TYPE_OR_IF] = "OR_IF",
	[NODE_TYPE_REDIR_IN] = "REDIR_IN",
	[NODE_TYPE_REDIR_OUT] = "REDIR_OUT",
	[NODE_TYPE_HEREDOC] = "HEREDOC",
	[NODE_TYPE_REDIR_APPEND] = "REDIR_APPEND",
	[NODE_TYPE_SUBSHELL] = "SUBSHELL",
	};

	if (type >= 0 && type <= NODE_TYPE_SUBSHELL)
		ft_putendl_fd((char *)types[type], STDOUT_FILENO);
	else
		ft_putendl_fd("UNKNOWN", STDOUT_FILENO);
}

static void	print_node(char *node_type, char *node_value)
{
	ft_putstr_fd(node_type, STDOUT_FILENO);
	ft_putendl_fd(node_value, STDOUT_FILENO);
}
