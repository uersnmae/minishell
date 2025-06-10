/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:13:06 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/05 14:11:18 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

ssize_t	ft_get_param_width(t_flags *flag, va_list params)
{
	void	*buf;

	if (flag->specifier == 's' || flag->specifier == 'p')
	{
		buf = va_arg(params, void *);
		if (buf == NULL)
			return (6 * (flag->precision >= 6 || flag->precision == -1 || \
			flag->specifier == 'p') - (flag->specifier == 'p'));
		if (flag->specifier == 'p')
			return (ft_numlen(0, HEX, UNSIGNED, buf) + 2);
		if ((ssize_t)ft_strlen(buf) > flag->precision && flag->precision != -1)
			return (flag->precision);
		if ((ssize_t)ft_strlen(buf) <= flag->precision || flag->precision == -1)
			return (ft_strlen(buf));
	}
	else if (flag->specifier == 'c')
		return (1);
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		return (ft_numlen(va_arg(params, int), DEC, SIGNED, NULL));
	else if (flag->specifier == 'u')
		return (ft_numlen(va_arg(params, int), DEC, UNSIGNED, NULL));
	else if (flag->specifier == 'x' || flag->specifier == 'X')
		return (ft_numlen(va_arg(params, int), HEX, UNSIGNED, NULL));
	return (0);
}
