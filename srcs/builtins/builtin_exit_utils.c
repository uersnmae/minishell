/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:29:19 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/16 10:29:35 by hakslee          ###   ########.fr       */
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

int	is_numeric(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || s[i] == '\0')
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

long	convert_to_long(const char *num, int sign)
{
	long	result;
	size_t	i;

	result = 0;
	i = 0;
	while (num[i])
	{
		result = result * 10 + (num[i] - '0');
		i++;
	}
	return (result * sign);
}
