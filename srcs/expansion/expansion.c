/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:05:50 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/07 21:49:02 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "env_table.h"
#include "expansion.h"

static char	*expand_single_quote(const char *in, size_t *idx);
static char	*expand_double_quote(const char *in, size_t *idx, t_shell *shell);
static char	*expand_unquoted(const char *in, size_t *idx, t_shell *shell);
static char	*expand_val_word(char *in, t_shell *shell);

void	expand_tokens(t_token *token, t_shell *shell)
{
	while (token)
	{
		if (token->type == TK_WORD)
			token->value = expand_val_word(token->value, shell);
		token = token->next;
	}
}

static char	*expand_val_word(char *in, t_shell *shell)
{
	size_t	i;
	char	*result;
	char	*temp;
	char	*part;

	i = 0;
	result = ft_strdup("");
	while (in[i])
	{
		if (in[i] == '\'')
			part = expand_single_quote(in, &i);
		else if (in[i] == '\"')
			part = expand_double_quote(in, &i, shell);
		else
			part = expand_unquoted(in, &i, shell);
		temp = ft_strjoin(result, part);
		if (temp == NULL)
			exit (EXIT_FAILURE);
		free(result);
		free(part);
		result = temp;
	}
	free(in);
	return (result);
}

static char	*expand_single_quote(const char *in, size_t *idx)
{
	size_t	start;
	size_t	len;
	char	*seg;

	if (in[*idx] != '\'')
		return (ft_strdup(""));
	start = *idx + 1;
	len = 0;
	while (in[start + len] && in[start + len] != '\'')
		len++;
	seg = ft_substr(in, start, len);
	if (seg == NULL)
		exit(EXIT_FAILURE);
	*idx = start + len + (in[start + len] == '\'');
	return (seg);
}

static char	*expand_double_quote(const char *in, size_t *idx, t_shell *shell)
{
	char	*acc;
	char	*seg;
	char	*tmp;

	if (in[*idx] == '\"')
		(*idx)++;
	acc = ft_strdup("");
	if (acc == NULL)
		exit(EXIT_FAILURE);
	while (in[*idx] && in[*idx] != '"')
	{
		if (in[*idx] == '$')
			seg = sub_var(in + *idx, idx, shell);
		else
			seg = ft_substr(in + (*idx)++, 0, 1);
		tmp = ft_strjoin(acc, seg);
		free(acc);
		free(seg);
		acc = tmp;
	}
	if (in[*idx] == '"')
		(*idx)++;
	return (acc);
}

static char	*expand_unquoted(const char *in, size_t *idx, t_shell *shell)
{
	char	*res;

	if (in[*idx] == '$')
		res = sub_var(in + *idx, idx, shell);
	else
	{
		res = ft_substr(in + *idx, 0, 1);
		if (res == NULL)
			exit(EXIT_FAILURE);
		(*idx)++;
	}
	return (res);
}
