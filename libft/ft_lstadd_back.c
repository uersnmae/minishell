/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:26 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/03 12:21:32 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if ((*lst) == (void *)0)
		(*lst) = new;
	else
	{
		current = (*lst);
		while (current->next != (void *)0)
			current = current->next;
		current->next = new;
	}
}
