/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:22:01 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/04 00:06:19 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

ssize_t	ft_putstr_printf(char *str, t_flags *flag, int fd)
{
	ssize_t	len;

	if ((str == NULL && flag->precision >= 6) || \
		(str == NULL && flag->precision == -1))
		return (write(fd, "(null)", 6));
	else if (str == NULL && flag->precision < 6)
		return (0);
	else
	{
		len = ft_strlen(str);
		if ((flag->precision < len && flag->precision > 0) || \
			flag->precision == 0)
			len = flag->precision;
	}
	return (write(fd, str, len));
}

ssize_t	ft_put_memory_printf(void *memory, int fd)
{
	uintptr_t	memnum;
	size_t		len;
	size_t		plen;
	char		addr_str[20];

	if (memory == (void *)0)
		return (write(fd, "(nil)", 5));
	addr_str[0] = '0';
	addr_str[1] = 'x';
	memnum = (uintptr_t)memory;
	len = 0;
	while (memnum > 0)
	{
		memnum /= 16;
		len++;
	}
	addr_str[2 + len] = '\0';
	memnum = (uintptr_t)memory;
	plen = len;
	while (memnum > 0)
	{
		addr_str[2 + --plen] = "0123456789abcdef"[memnum % 16];
		memnum /= 16;
	}
	return (write(fd, addr_str, len + 2));
}

static ssize_t	ft_putnbr_buf(unsigned int nbr, char **buf, int sign, char neg)
{
	ssize_t	buf_len;
	ssize_t	index;

	buf_len = ft_numlen(nbr, DEC, sign, NULL) + neg;
	*buf = ft_calloc(buf_len + 1, sizeof(char));
	if (!(*buf))
		return (-1);
	if (neg)
		(*buf[0]) = '-';
	index = buf_len - 1;
	while (index >= neg)
	{
		(*buf)[index] = nbr % 10 + '0';
		nbr /= 10;
		if (index == neg)
			break ;
		index--;
	}
	return (buf_len);
}

ssize_t	ft_putnbr_printf(t_flags *flag, int nbr, int sign, int fd)
{
	ssize_t			ret;
	ssize_t			buf_len;
	unsigned int	pnbr;
	char			neg;
	char			*buf;

	if (flag->precision == 0 && nbr == 0)
		return (0);
	neg = 0;
	if (nbr < 0 && sign == SIGNED && flag->none)
	{
		neg = 1;
		pnbr = (unsigned int)(-nbr);
	}
	else if (nbr < 0 && sign == SIGNED && !flag->none)
		pnbr = (unsigned int)(-nbr);
	else
		pnbr = (unsigned int)nbr;
	buf_len = ft_putnbr_buf(pnbr, &buf, sign, neg);
	if (buf_len < 0)
		return (-1);
	ret = write(fd, buf, buf_len);
	free(buf);
	return (ret);
}

ssize_t	ft_hex_putnbr_printf(t_flags *flag, unsigned int n, int base, int fd)
{
	size_t		buf_len;
	size_t		write_len;
	ssize_t		ret;
	char		*buf;

	if (flag->precision == 0 && n == 0)
		return (0);
	buf_len = ft_numlen(n, HEX, UNSIGNED, NULL);
	write_len = buf_len;
	buf = (char *)ft_calloc(buf_len, sizeof(char));
	if (!buf)
		return (0);
	while (buf_len--)
	{
		if (base == UPPERCASE)
			buf[buf_len] = "0123456789ABCDEF"[n % 16];
		else if (base == LOWERCASE)
			buf[buf_len] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	ret = write(fd, buf, write_len);
	free(buf);
	return (ret);
}
