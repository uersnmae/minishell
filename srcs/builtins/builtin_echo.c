/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:35:15 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/26 20:29:37 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <unistd.h>

static int	is_n_option(const char *s)
{
	int	i;

	if (s == NULL || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

int	builtin_echo(char **argv)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (argv[i] && is_n_option(argv[i]))
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
