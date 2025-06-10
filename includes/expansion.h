/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:15:53 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 23:36:16 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include "tokenizer.h"
# include "env_table.h"

void	expand_tokens(t_token *token, t_shell *shell);

char	*get_env_value(t_env_table *env, const char *key);
char	*sub_var(const char *str, size_t *idx, t_shell *shell);
void	split_on_ifs(t_token **tokens);

#endif
