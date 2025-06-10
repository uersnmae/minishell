/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:43:01 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/03 11:29:06 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"

int	is_boundary(char c)
{
	return (ft_isspace(c) || ft_strchr("|<>", c));
}

void	append_token(t_token **head, t_token **tail,
						const char *start, size_t raw_len)
{
	char			*lexeme;
	t_token			*tok;
	size_t			new_len;
	bool			is_subs;

	is_subs = (raw_len >= 2 && start[0] == '(' && start[raw_len - 1] == ')');
	lexeme = ft_strndup(start + is_subs, raw_len - 2 * is_subs);
	if (!lexeme)
		exit (EXIT_FAILURE);
	new_len = ft_strlen(lexeme);
	if (is_subs)
		tok = get_new_tok(TK_SUBSHELL, lexeme, new_len);
	else
		tok = get_new_tok(TK_WORD, lexeme, new_len);
	if (!is_subs && raw_len >= 2)
		if ((start[0] == '\'' && start[raw_len - 1] == '\'')
			|| (start[0] == '"' && start[raw_len - 1] == '"'))
			tok->quoted = true;
	if (*tail)
		(*tail)->next = tok;
	else
		*head = tok;
	*tail = tok;
}
