/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:51:26 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/06 01:25:09 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
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

int	builtin_pwd(char **argv)
{
	char	buf[1024];

	(void)argv;
	if (getcwd(buf, 1024) == NULL)
		return (1);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char		*path;

	if (argv[1])
		path = argv[1];
	else
		path = (char *)env_get(shell->env, "HOME");
	if (path == NULL || chdir(path) != 0)
		return (1);
	return (0);
}

int	builtin_exit(char **argv)
{
	if (argv[1])
		exit(ft_atoi(argv[1]));
	exit(0);
}
