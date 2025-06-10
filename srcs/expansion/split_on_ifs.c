/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_on_ifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:37:29 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/03 11:33:40 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"
#include "tokenizer.h"

static bool	is_assignment_word(char *s)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(s[i]) || s[i] == '_'))
		return (false);
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (false);
		i++;
	}
	return (s[i] == '=');
}

static char	**ft_split_ifs(char *s)
{
	char	*dup;
	char	**res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	dup = ft_strdup(s);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (dup[i])
	{
		if (ft_isspace(dup[i]))
			dup[i] = ' ';
		i++;
	}
	res = ft_split(dup, ' ');
	if (res == NULL)
	{
		free(dup);
		return (NULL);
	}
	free(dup);
	return (res);
}

static t_token	*insert_split_nodes(t_token *curr, char **parts)
{
	size_t	i;
	t_token	*tail;
	t_token	*token;

	tail = curr;
	i = 1;
	while (parts[i] != NULL)
	{
		token = malloc(sizeof(t_token));
		if (token == NULL)
			break ;
		token->type = TK_WORD;
		token->value = parts[i++];
		token->next = tail->next;
		tail->next = token;
		tail = token;
	}
	return (tail->next);
}

static t_token	*process_one_ifsplit(t_token *curr)
{
	char	**parts;
	t_token	*next;

	if (curr->type == TK_SUBSHELL)
		return (curr->next);
	if (curr->quoted || is_assignment_word(curr->value))
		return (curr->next);
	parts = ft_split_ifs(curr->value);
	if (parts && parts[0] && parts[1])
	{
		free(curr->value);
		curr->value = parts[0];
		next = insert_split_nodes(curr, parts);
	}
	else
	{
		if (parts)
			free(parts[0]);
		next = curr->next;
	}
	free(parts);
	return (next);
}

void	split_on_ifs(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
		curr = process_one_ifsplit(curr);
}
