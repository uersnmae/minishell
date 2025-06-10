/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:51:26 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/16 11:42:14 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "ast.h"
#include "builtins.h"
#include "minishell.h"
#include "libft.h"

static void	print_numeric_error(const char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static int	check_long_range(const char *num, int sign)
{
	const char	*limit;
	int			len_num;
	int			len_limit;

	if (sign == 1)
		limit = "9223372036854775807";
	else
		limit = "9223372036854775808";
	len_num = ft_strlen(num);
	len_limit = ft_strlen(limit);
	if (len_num < len_limit)
		return (0);
	if (len_num > len_limit)
		return (1);
	if (ft_strncmp((char *)num, (char *)limit, ft_strlen((char *)num)) > 0)
		return (1);
	return (0);
}

static long	parse_numeric_argument(const char *arg)
{
	int			sign;
	const char	*num = arg;

	errno = 0;
	sign = 1;
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	if (check_long_range(num, sign))
	{
		errno = ERANGE;
		return (0);
	}
	return (convert_to_long(num, sign));
}

int	exit_code_input(t_shell *shell, int running, int status, char *argv)
{
	print_numeric_error(argv);
	shell->running = running;
	shell->last_status = (unsigned char)status;
	return (shell->last_status);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	long	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
	{
		shell->running = 0;
		return (shell->last_status);
	}
	if (!is_numeric(argv[1]))
		return (exit_code_input(shell, 0, 2, argv[1]));
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_code = parse_numeric_argument(argv[1]);
	if (errno == ERANGE)
		return (exit_code_input(shell, 0, 2, argv[1]));
	shell->running = false;
	shell->last_status = (unsigned char)exit_code;
	return (shell->last_status);
}
