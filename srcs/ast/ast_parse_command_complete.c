/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command_complete.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:58:39 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/06 17:42:44 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ast.h"
#include "minishell.h"

t_ast_node	*ast_parse_complete_command(t_token **token)
{
	return (ast_parse_pipe(token));
}
