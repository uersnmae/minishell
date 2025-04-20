/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:28:43 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/03 09:28:44 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	index;

	if (s == (void *)0 || f == (void *)0)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		f(index, (s + index));
		index++;
	}
}
