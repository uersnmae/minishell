/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:37:58 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/05 13:50:41 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t	ft_numlen(long nbr, int base, int sign, void *ptr)
{
	size_t		len;
	uintptr_t	pnbr;

	len = 1;
	if (nbr < 0 && sign == SIGNED && base == DEC)
	{
		len++;
		pnbr = (unsigned int)(-nbr);
	}
	else
		pnbr = (unsigned int)nbr;
	if (ptr != NULL)
		pnbr = (uintptr_t)ptr;
	while (pnbr >= (uintptr_t)base)
	{
		len++;
		pnbr /= base;
	}
	return (len);
}

ssize_t	ft_print_format(t_flags *flag, va_list params, int fd)
{
	unsigned char	c;

	c = 0;
	if (flag->specifier == 'c')
	{
		c = (unsigned char)va_arg(params, int);
		return (write(fd, &c, 1));
	}
	else if (flag->specifier == 's')
		return (ft_putstr_printf(va_arg(params, char *), flag, fd));
	else if (flag->specifier == 'p')
		return (ft_put_memory_printf(va_arg(params, void *), fd));
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		return (ft_putnbr_printf(flag, va_arg(params, int), SIGNED, fd));
	else if (flag->specifier == 'u')
		return (ft_putnbr_printf(flag, va_arg(params, int), UNSIGNED, fd));
	else if (flag->specifier == 'x')
		return (ft_hex_putnbr_printf(flag, va_arg(params, int), LOWERCASE, fd));
	else if (flag->specifier == 'X')
		return (ft_hex_putnbr_printf(flag, va_arg(params, int), UPPERCASE, fd));
	else if (flag->specifier == '%')
		return (write(fd, "%", 1));
	else
		return (-1);
}
