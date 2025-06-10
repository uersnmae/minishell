/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:41:13 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/03 11:26:26 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

typedef enum e_toktype
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_REDIR_APP,
	TK_SUBSHELL,
	TK_AND_IF,
	TK_OR_IF,
	TK_ERROR,
	TK_EOF
}	t_toktype;

typedef struct s_token
{
	t_toktype		type;
	bool			quoted;
	size_t			length;
	char			*value;
	struct s_token	*next;
}	t_token;

void	free_tokens(t_token **head);
t_token	*get_eof_tok(t_token **head);
t_token	*get_new_tok(t_toktype type,
			char *value,
			size_t length);
int		check_token_error(t_token **head);

void	handle_word(const char **p, t_token **head, t_token **tail);

int		tokenize(const char *input, t_token **head);

void	expand_word(const char **p_input, t_token **token);

#endif
