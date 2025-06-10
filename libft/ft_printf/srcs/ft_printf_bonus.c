/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:24:30 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/05 09:41:00 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

static void	ft_flag_init(t_flags *flag)
{
	flag->precision = -1;
	flag->width = 0;
	flag->left_align = 0;
	flag->zero_padding = 0;
	flag->show_sign = 0;
	flag->space = 0;
	flag->alternate = 0;
	flag->none = 1;
	flag->specifier = 0;
}

static ssize_t	ft_read_str(const char *str, t_flags *flag, \
						va_list params, int fd)
{
	ssize_t	str_printed;
	int		index;

	str_printed = 0;
	index = 0;
	while (str[index])
	{
		ft_flag_init(flag);
		if (str[index] == '%' && str[index + 1])
		{
			ft_parse(str, &index, flag);
			str_printed += ft_print_params(flag, params, fd);
			if (str_printed < 0)
				return (-1);
		}
		else
		{
			if (write(fd, &str[index], fd) < 0)
				return (-1);
			str_printed += 1;
		}
		index++;
	}
	return (str_printed);
}

int	ft_printf(const char *str, ...)
{
	ssize_t	printed;
	va_list	params;
	t_flags	*flag;

	flag = (t_flags *)malloc(sizeof(t_flags));
	if (!flag)
		return (-1);
	if (str == NULL)
		return (0);
	va_start(params, str);
	printed = ft_read_str(str, flag, params, STDOUT_FILENO);
	va_end(params);
	free(flag);
	return (printed);
}
