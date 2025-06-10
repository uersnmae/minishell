/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:43:02 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 22:51:16 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "tokenizer.h"

static void	skip_space(const char **p)
{
	while (**p && ft_isspace(**p))
		(*p)++;
}

static void	set_token_type(t_token *tok)
{
	while (tok)
	{
		if (tok->value[0] == '&' || tok->value[0] == '|' || tok->value[0] == '<'
			|| tok->value[0] == '>')
		{
			if (ft_strncmp(tok->value, "<", ft_strlen(tok->value)) == 0)
				tok->type = TK_REDIR_IN;
			else if (ft_strncmp(tok->value, ">", ft_strlen(tok->value)) == 0)
				tok->type = TK_REDIR_OUT;
			else if (ft_strncmp(tok->value, "<<", ft_strlen(tok->value)) == 0)
				tok->type = TK_HEREDOC;
			else if (ft_strncmp(tok->value, ">>", ft_strlen(tok->value)) == 0)
				tok->type = TK_REDIR_APP;
			else if (ft_strncmp(tok->value, "|", ft_strlen(tok->value)) == 0)
				tok->type = TK_PIPE;
			else if (ft_strncmp(tok->value, "&&", ft_strlen(tok->value)) == 0)
				tok->type = TK_AND_IF;
			else if (ft_strncmp(tok->value, "||", ft_strlen(tok->value)) == 0)
				tok->type = TK_OR_IF;
			else
				tok->type = TK_ERROR;
		}
		tok = tok->next;
	}
}

static bool	check_quotes(const char *input)
{
	bool	in_single;
	bool	in_double;
	size_t	index;

	index = 0;
	in_single = false;
	in_double = false;
	while (input[index])
	{
		if (input[index] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[index] == '"' && !in_single)
			in_double = !in_double;
		index++;
	}
	if (in_single || in_double)
		ft_putendl_fd("invalid syntax: unmatched quote", STDERR_FILENO);
	return (in_single || in_double);
}

static bool	check_paren(const char *input)
{
	size_t	paren_count;
	size_t	index;

	paren_count = 0;
	index = 0;
	while (input[index])
	{
		if (input[index] == '(')
			paren_count++;
		else if (input[index] == ')')
			paren_count--;
		index++;
	}
	if (paren_count != 0)
	{
		ft_putendl_fd("invalid syntax: unmatched parenthesis", STDERR_FILENO);
		return (true);
	}
	return (false);
}

int	tokenize(const char *input, t_token **head)
{
	const char		*p = input;
	t_token			*tail;

	*head = NULL;
	tail = NULL;
	if (check_quotes(input) || check_paren(input))
		return (0);
	skip_space(&p);
	while (*p)
	{
		handle_word(&p, head, &tail);
		skip_space(&p);
	}
	set_token_type(*head);
	if (tail)
		tail->next = NULL;
	else
		*head = NULL;
	return (check_token_error(head));
}
