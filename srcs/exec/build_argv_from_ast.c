/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv_from_ast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:21:33 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 12:32:14 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"
#include "tokenizer.h"
#include "expansion.h"
#include "wildcard_bonus.h"

static t_list	*collect_word_tokens(t_token *tokens)
{
	t_list	*args;
	t_token	*tk;

	tk = tokens;
	args = NULL;
	while (tk != NULL)
	{
		if (tk->type == TK_REDIR_IN || tk->type == TK_REDIR_OUT
			|| tk->type == TK_HEREDOC || tk->type == TK_REDIR_APP)
		{
			if (tk->next)
				tk = tk->next->next;
			else
				break ;
			continue ;
		}
		ft_lstadd_back(&args, ft_lstnew(ft_strdup(tk->value)));
		tk = tk->next;
	}
	return (args);
}

static t_list	*wildcard_expand_args(t_list *args)
{
	t_list	*expanded;

	expanded = expand_wildcard_arguments(args);
	ft_lstclear(&args, free);
	return (expanded);
}

static char	**list_to_argv(t_list *list)
{
	t_list	*node;
	t_list	*tmp;
	char	**argv;
	int		argc;
	int		i;

	argc = ft_lstsize(list);
	argv = ft_calloc((argc + 1), sizeof(char *));
	if (argv == NULL)
	{
		ft_lstclear(&list, free);
		return (NULL);
	}
	i = 0;
	node = list;
	while (node != NULL)
	{
		argv[i++] = node->content;
		tmp = node;
		node = node->next;
		free(tmp);
	}
	argv[i] = NULL;
	return (argv);
}

char	**build_argv_from_tokens(t_token *tokens, t_shell *shell)
{
	t_list	*args;
	t_list	*globbed;

	expand_tokens(tokens, shell);
	split_on_ifs(&tokens);
	args = collect_word_tokens(tokens);
	globbed = wildcard_expand_args(args);
	return (list_to_argv(globbed));
}
