/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:08:29 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/06 11:10:29 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

ssize_t	ft_print_flag(t_flags *flag, va_list params, int fd)
{
	ssize_t	printed;
	ssize_t	temp;
	ssize_t	param_width;
	ssize_t	sign;
	va_list	params_copy;

	printed = ft_alternate(flag, params, fd);
	if (printed < 0)
		return (-1);
	sign = ft_show_sign_space(flag, params, fd);
	if (sign < 0)
		return (-1);
	printed += sign;
	va_copy(params_copy, params);
	param_width = ft_get_param_width(flag, params_copy);
	va_end(params_copy);
	temp = 0;
	if (flag->precision > param_width - sign)
		temp = ft_precision(flag, param_width - sign, fd);
	else if (!flag->left_align && flag->precision == -1 && flag->zero_padding)
		temp = ft_zero_padding(flag, param_width, fd);
	if (temp < 0)
		return (-1);
	return (printed + temp);
}
