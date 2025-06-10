/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:39:58 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/05 13:44:49 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# define FT_PRINTF_BONUS_H
# define SIGNED 1
# define UNSIGNED 0
# define TRUE 1
# define FALSE 0
# define DEC 10u
# define HEX 16u

typedef struct s_flags
{
	ssize_t	precision;
	ssize_t	width;
	int		left_align;
	int		zero_padding;
	int		show_sign;
	int		space;
	int		alternate;
	int		none;
	char	specifier;
}	t_flags;

/*============================ft_printf_bonus.c==============================*/
int		ft_printf(const char *str, ...);
/*============================ft_print_format.c==============================*/
size_t	ft_numlen(long nbr, int base, int sign, void *ptr);
ssize_t	ft_print_format(t_flags *flag, va_list params, int fd);
/*============================ft_print_format_utils.c========================*/
ssize_t	ft_putstr_printf(char *str, t_flags *flag, int fd);
ssize_t	ft_put_memory_printf(void *memory, int fd);
ssize_t	ft_putnbr_printf(t_flags *flag, int nbr, int sign, int fd);
ssize_t	ft_hex_putnbr_printf(t_flags *flag, unsigned int n, int base, int fd);
/*============================ft_parse.c=====================================*/
void	ft_parse(const char *str, int *index, t_flags *flag);
/*============================ft_print_flags_option1s_bonus.c================*/
ssize_t	ft_alternate(t_flags *flag, va_list params, int fd);
ssize_t	ft_show_sign_space(t_flags *flag, va_list params, int fd);
ssize_t	ft_precision(t_flags *flag, ssize_t param_width, int fd);
ssize_t	ft_zero_padding(t_flags *flag, ssize_t printed_len, int fd);
ssize_t	ft_fill_width(t_flags *flag, ssize_t printed_len, int fd);
/*============================ft_print_flags_utils1_bonus.c===================*/
ssize_t	ft_print_params(t_flags *flag, va_list params, int fd);
/*============================ft_print_flags_utils2_bonus.c===================*/
ssize_t	ft_get_param_width(t_flags *flag, va_list params);
/*============================ft_print_flags_bonus.c=========================*/
ssize_t	ft_print_flag(t_flags *flag, va_list params, int fd);

#endif
