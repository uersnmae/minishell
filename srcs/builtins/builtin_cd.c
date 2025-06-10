/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:35:04 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/08 17:51:11 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static int	check_args(char **argv)
{
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	get_target(char **argv, t_shell *shell,	\
		char **target, int *print_path)
{
	*print_path = 0;
	if (argv[1] == NULL)
	{
		*target = (char *)env_get(shell->env, "HOME");
		if (!*target)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			return (1);
		}
	}
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		*target = (char *)env_get(shell->env, "OLDPWD");
		if (!*target)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			return (1);
		}
		*print_path = 1;
	}
	else
		*target = argv[1];
	return (0);
}

static int	change_dir_and_update(t_shell *shell, char *target, char *new_pwd)
{
	char	*old_pwd;

	old_pwd = (char *)env_get(shell->env, "PWD");
	if (chdir(target) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)target, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	if (old_pwd)
		env_set(shell->env, "OLDPWD", old_pwd);
	if (!getcwd(new_pwd, 1024))
	{
		ft_putendl_fd("cd: error retrieving current directory", STDERR_FILENO);
		return (1);
	}
	env_set(shell->env, "PWD", new_pwd);
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char		*target;
	char		new_pwd[1024];
	int			print_path;

	if (check_args(argv))
		return (1);
	if (get_target(argv, shell, &target, &print_path))
		return (1);
	if (change_dir_and_update(shell, target, new_pwd))
		return (1);
	if (print_path)
		ft_putendl_fd(new_pwd, STDOUT_FILENO);
	return (0);
}
