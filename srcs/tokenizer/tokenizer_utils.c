/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 01:07:35 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/03 11:26:52 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "tokenizer.h"

void	free_tokens(t_token **head)
{
	t_token	*curr;
	t_token	*next;

	if (head == NULL || *head == NULL)
		return ;
	curr = *head;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
	*head = NULL;
}

t_token	*get_eof_tok(t_token **head)
{
	t_token	*eof_tok;

	eof_tok = malloc(sizeof(t_token));
	if (eof_tok == NULL)
	{
		free_tokens(head);
		exit(EXIT_FAILURE);
	}
	eof_tok->type = TK_EOF;
	eof_tok->value = NULL;
	eof_tok->length = 0;
	eof_tok->next = NULL;
	return (eof_tok);
}

t_token	*get_new_tok(t_toktype type,
					char *value,
					size_t length)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (tok == NULL)
		exit(EXIT_FAILURE);
	tok->type = type;
	tok->value = value;
	tok->length = length;
	tok->next = NULL;
	tok->quoted = false;
	return (tok);
}

int	check_token_error(t_token **head)
{
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		if (curr->type == TK_ERROR)
		{
			ft_putendl_fd("Invalid Operator!!", STDERR_FILENO);
			free_tokens(head);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}
