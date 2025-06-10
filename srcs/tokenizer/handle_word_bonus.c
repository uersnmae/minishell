/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:42:27 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 19:18:48 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tokenizer.h"
#include "handle_word.h"

static bool	parse_subshell(const char **p, t_token **head, t_token **tail)
{
	const char	*start;
	int			depth;

	if (**p != '(')
		return (false);
	start = *p;
	(*p)++;
	depth = 1;
	while (**p && depth > 0)
	{
		if (**p == '(')
			depth++;
		else if (**p == ')')
			depth--;
		(*p)++;
	}
	append_token(head, tail, start, *p - start);
	return (true);
}

static void	handle_boundary(const char **p, t_token **head, t_token **tail)
{
	size_t	len;
	char	curr;
	char	next;

	len = 1;
	curr = **p;
	next = *(*p + 1);
	if ((curr == '<' || curr == '>' || curr == '|' || curr == '&')
		&& next == curr)
		len = 2;
	append_token(head, tail, *p, len);
	*p += len;
}

static void	handle_unquoted(const char **p, t_token **head, t_token **tail)
{
	const char	*start = *p;
	char		quote;

	while (**p && !is_boundary(**p))
	{
		if (**p == '\'' || **p == '"')
		{
			quote = **p;
			(*p)++;
			while (**p && **p != quote)
				(*p)++;
			if (**p == quote)
				(*p)++;
		}
		else if (is_boundary(**p))
			break ;
		else
			(*p)++;
	}
	append_token(head, tail, start, *p - start);
}

void	handle_word(const char **p, t_token **head, t_token **tail)
{
	if (parse_subshell(p, head, tail))
		return ;
	if (is_boundary(**p))
		handle_boundary(p, head, tail);
	else
		handle_unquoted(p, head, tail);
}
