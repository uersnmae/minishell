/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:28:24 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/03 09:28:25 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd)
{
	if (s == (void *)0)
		return ;
	while (*s)
		ft_putchar_fd(*(s++), fd);
}
