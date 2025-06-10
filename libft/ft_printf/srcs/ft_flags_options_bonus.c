/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_options_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:29:34 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/06 11:10:58 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

ssize_t	ft_alternate(t_flags *flag, va_list params, int fd)
{
	ssize_t			printed;
	unsigned int	temp;
	va_list			params_copy;

	printed = 0;
	if (flag->alternate)
	{
		va_copy(params_copy, params);
		temp = va_arg(params_copy, int);
		if (temp == 0)
			return (0);
		va_end(params_copy);
		if (flag->specifier == 'x')
			printed = write(fd, "0x", 2);
		else if (flag->specifier == 'X')
			printed = write(fd, "0X", 2);
	}
	return (printed);
}

ssize_t	ft_show_sign_space(t_flags *flag, va_list params, int fd)
{
	ssize_t	printed;
	va_list	params_copy;
	int		num;

	printed = 0;
	va_copy(params_copy, params);
	num = va_arg(params_copy, int);
	if (flag->show_sign || flag->space || \
		flag->zero_padding || flag->precision >= 0)
	{
		if (flag->specifier == 'd' || flag->specifier == 'i')
		{
			if (num < 0)
				printed = write(fd, "-", 1);
			else if (num >= 0 && flag->show_sign == 1)
				printed = write(fd, "+", 1);
			else if (num >= 0 && flag->space == 1)
				printed = write(fd, " ", 1);
		}
	}
	va_end(params_copy);
	return (printed);
}

ssize_t	ft_precision(t_flags *flag, ssize_t param_width, int fd)
{
	ssize_t	printed;
	char	*buf;

	printed = 0;
	buf = malloc(flag->precision - param_width);
	if (!buf)
		return (-1);
	if (flag->specifier != 's' && flag->specifier != 'c')
		ft_memset(buf, '0', (flag->precision - param_width));
	if (flag->precision - param_width > 0 && param_width != 0 && \
		flag->specifier != 's')
		printed = write(fd, buf, flag->precision - param_width);
	if (printed < 0)
		return (-1);
	free(buf);
	return (printed);
}

ssize_t	ft_zero_padding(t_flags *flag, ssize_t printed_len, int fd)
{
	ssize_t	printed;
	char	*buf;

	printed = 0;
	if (flag->width > printed_len && flag->zero_padding)
	{
		buf = malloc(flag->width - printed_len);
		if (!buf)
			return (-1);
		ft_memset(buf, '0', flag->width - printed_len);
		printed = write(fd, buf, flag->width - printed_len);
		free(buf);
	}
	return (printed);
}

ssize_t	ft_fill_width(t_flags *flag, ssize_t printed_len, int fd)
{
	char	*buf;
	ssize_t	printed;
	ssize_t	width_len;

	printed = 0;
	width_len = flag->width - printed_len;
	if (width_len > 0 && !flag->zero_padding && flag->specifier != '%')
	{
		buf = (char *)ft_calloc(sizeof(char), width_len);
		if (!buf)
			return (-1);
		ft_memset(buf, ' ', width_len);
		printed = write(fd, buf, width_len);
		free(buf);
	}
	return (printed);
}
