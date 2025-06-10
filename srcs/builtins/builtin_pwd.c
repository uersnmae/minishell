/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:35:46 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/08 14:35:52 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <unistd.h>

int	builtin_pwd(char **argv)
{
	char	buf[1024];

	(void)argv;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		ft_putendl_fd("pwd: error retrieving current directory", STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	return (0);
}
