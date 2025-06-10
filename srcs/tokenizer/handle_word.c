/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:42:27 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/08 14:23:15 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenizer.h"
#include "handle_word.h"

static void	handle_boundary(const char **p, t_token **head, t_token **tail)
{
	size_t	len;
	char	curr;
	char	next;

	len = 1;
	curr = **p;
	next = *(*p + 1);
	if ((curr == '<' || curr == '>') && next == curr)
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
	if ((**p == '\'' || **p == '"') || !is_boundary(**p))
		handle_unquoted(p, head, tail);
	else
		handle_boundary(p, head, tail);
}
