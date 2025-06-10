/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:51:43 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/16 17:29:28 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "builtins.h"
#include "env_table.h"
#include "minishell.h"

int	builtin_env(char **argv, t_shell *shell)
{
	int		i;
	char	**envp;

	if (argv[1])
	{
		write(STDERR_FILENO, "env: too many arguments\n", 24);
		return (1);
	}
	envp = env_to_envp(shell->env);
	i = 0;
	while (envp[i])
	{
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	env_free_envp(envp);
	return (0);
}
