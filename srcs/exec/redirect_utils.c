/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:31:24 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 15:50:16 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#include "libft.h"
#include "minishell.h"

static int	simple_match(char *pat, char *name)
{
	const char	*star = ft_strchr(pat, '*');
	size_t		pre;
	size_t		suf;
	size_t		len;

	if (star == NULL)
		return (ft_strncmp(pat, name, ft_strlen(name) + 1) == 0);
	pre = star - pat;
	if (ft_strncmp(pat, name, pre) != 0)
		return (0);
	suf = ft_strlen(star + 1);
	len = ft_strlen(name);
	if (len < pre + suf)
		return (0);
	return (ft_strncmp((char *)star + 1, \
					name + (len - suf), ft_strlen(star + 1) + 1) == 0);
}

static void	update_wc_match(char *name, char *pattern, int *n, char **single)
{
	if (!simple_match(pattern, name))
		return ;
	(*n)++;
	if (*n == 1 && single)
		*single = ft_strdup(name);
	else if (*n == 2 && single)
	{
		free(*single);
		*single = NULL;
	}
}

static int	count_wc_matches(char *pattern, char **single)
{
	DIR				*d;
	struct dirent	*e;
	int				n;

	n = 0;
	if (single)
		*single = NULL;
	d = opendir(".");
	if (!d)
		return (0);
	e = readdir(d);
	while (e != NULL)
	{
		update_wc_match(e->d_name, pattern, &n, single);
		e = readdir(d);
	}
	closedir(d);
	return (n);
}

char	*handle_redirect_pattern(char *token, t_shell *shell)
{
	char	*single;
	int		m;

	if (!ft_strchr(token, '*'))
		return (ft_strdup(token));
	single = NULL;
	m = count_wc_matches(token, &single);
	if (m > 1)
	{
		shell->last_status = error_status(token,
				": ambiguous redirect", EXIT_FAILURE, true);
		exit(shell->last_status);
	}
	if (m == 1)
		return (single);
	return (ft_strdup(token));
}
