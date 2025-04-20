/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:29:12 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/05 19:56:29 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar_to_str(char c, char *nbr_str)
{
	unsigned int	len;

	len = ft_strlen(nbr_str);
	nbr_str[len] = c;
	nbr_str[len + 1] = '\0';
}

static void	ft_putnbr(int nb, unsigned int base_len, char *base, char *nbr_str)
{
	unsigned int	_nb;

	if (nb < 0)
	{
		ft_putchar_to_str('-', nbr_str);
		_nb = -nb;
	}
	else
		_nb = nb;
	if (_nb >= base_len)
		ft_putnbr(_nb / base_len, base_len, base, nbr_str);
	ft_putchar_to_str(base[_nb % base_len], nbr_str);
}

static int	ft_get_size(int nbr_num, int base_to_len)
{
	int	cnt;

	cnt = 0;
	if (nbr_num < 0)
		cnt++;
	if (nbr_num == 0)
		cnt = 1;
	while (nbr_num != 0)
	{
		nbr_num /= base_to_len;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		size;

	size = ft_get_size(n, 10);
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	if (ret == (void *)0)
		return ((void *)0);
	ft_putnbr(n, 10, "0123456789", ret);
	return (ret);
}
