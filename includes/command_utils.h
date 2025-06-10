/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:51:54 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 15:54:08 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "command_structs.h"
# include "minishell.h"

t_job		*flatten_jobs(t_ast_node *root, t_shell *shell);

t_command	*flatten_pipeline(t_ast_node *node, t_shell *shell);

t_redir		*build_redirs_from_ast(t_ast_node *node);

char		**build_argv_from_tokens(t_token *tokens, t_shell *shell);

bool		is_redir_node(const t_ast_node *node);

#endif
