/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:08:50 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/11 15:17:27 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>

#include "wildcard_bonus.h"

static bool	is_pattern_match(const char *pattern, const char *str);

static bool	is_pattern_match_helper(const char **pattern, const char **str)
{
	while (**pattern == '*')
		(*pattern)++;
	if (**pattern == '\0')
		return (true);
	while (**str != '\0')
	{
		if (is_pattern_match(*pattern, *str) == true)
			return (true);
		(*str)++;
	}
	return (false);
}

static bool	is_pattern_match(const char *pattern, const char *str)
{
	while (*pattern != '\0' && *str != '\0')
	{
		if (*pattern == '*')
			return (is_pattern_match_helper(&pattern, &str));
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (false);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}

static bool	open_entry(struct dirent **entry, DIR *dir)
{
	*entry = readdir(dir);
	if (*entry == NULL)
		return (false);
	return (true);
}

static bool	expand_wildcard_helper(const char *pattern, \
								struct dirent *entry, \
								t_list **matches, \
								bool *match_found)
{
	char	*dup;
	t_list	*node;

	if (is_pattern_match(pattern, entry->d_name) == true)
	{
		*match_found = true;
		dup = ft_strdup(entry->d_name);
		if (dup == NULL)
			return (false);
		node = ft_lstnew(dup);
		if (node == NULL)
		{
			free(dup);
			return (false);
		}
		ft_lstadd_back(matches, node);
		return (true);
	}
	return (true);
}

t_list	*expand_wildcard(const char *pattern)
{
	t_list			*matches;
	DIR				*dir;
	struct dirent	*entry;
	bool			match_found;

	match_found = false;
	dir = opendir(".");
	if (dir == NULL)
		return ((t_list *)WILDCARD_ERROR);
	matches = NULL;
	while (open_entry(&entry, dir) == true)
	{
		if (entry->d_name[0] == '.')
			continue ;
		if (!expand_wildcard_helper(pattern, entry, &matches, &match_found))
		{
			ft_lstclear(&matches, free);
			closedir(dir);
			return ((t_list *)WILDCARD_ERROR);
		}
	}
	closedir(dir);
	if (match_found == true)
		return (matches);
	return (NULL);
}
