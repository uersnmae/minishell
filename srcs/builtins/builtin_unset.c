/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:06:22 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/11 14:06:22 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "builtins.h"
#include "env_table.h"
#include "minishell.h"

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_unset(shell->env, argv[i]);
		i++;
	}
	return (0);
}
