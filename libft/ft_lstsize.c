/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:13:04 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/03 12:19:02 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		len;

	if (lst == (void *)0)
		return (0);
	current = lst;
	len = 1;
	while (current->next != (void *)0)
	{
		current = current->next;
		len++;
	}
	return (len);
}
