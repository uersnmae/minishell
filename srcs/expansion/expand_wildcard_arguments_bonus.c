/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_arguments_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:17:29 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/06 02:40:34 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wildcard_bonus.h"

static bool	expand_wildcard_arguments_helper(t_list **expanded, \
											t_list *matches, \
											char *arg)
{
	char	*dup;
	t_list	*node;

	if (matches == NULL)
	{
		dup = ft_strdup(arg);
		if (dup == NULL)
			return (false);
		node = ft_lstnew((void *)dup);
		if (node == NULL)
		{
			free(dup);
			return (false);
		}
		ft_lstadd_back(expanded, node);
	}
	else
		ft_lstadd_back(expanded, matches);
	return (true);
}

static t_list	*wrap_lstclear(t_list **expanded, t_list **argv)
{
	ft_lstclear(expanded, free);
	ft_lstclear(argv, free);
	return (NULL);
}

t_list	*expand_wildcard_arguments(t_list *argv)
{
	t_list	*expanded;
	t_list	*cur;
	t_list	*matches;

	expanded = NULL;
	cur = argv;
	while (cur != NULL)
	{
		if (ft_strchr((char *)cur->content, '*') != NULL)
		{
			matches = expand_wildcard(cur->content);
			if (matches == (t_list *)WILDCARD_ERROR \
			|| !expand_wildcard_arguments_helper(&expanded, \
									matches, cur->content))
				return (wrap_lstclear(&expanded, &argv));
		}
		else
			if (!expand_wildcard_arguments_helper(&expanded, \
									NULL, cur->content))
				return (wrap_lstclear(&expanded, &argv));
		cur = cur->next;
	}
	return (expanded);
}
