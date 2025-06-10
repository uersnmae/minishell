/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:50:34 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/15 11:41:38 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_shell *shell)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		shell->last_status = builtin_echo(argv);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		shell->last_status = builtin_pwd(argv);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		shell->last_status = builtin_cd(argv, shell);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		shell->last_status = builtin_env(argv, shell);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		shell->last_status = builtin_exit(argv, shell);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		shell->last_status = builtin_export(argv, shell);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		shell->last_status = builtin_unset(argv, shell);
	return (shell->last_status);
}
