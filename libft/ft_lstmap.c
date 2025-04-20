/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:26:29 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/04 13:19:20 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*iter;
	t_list	*ret;
	t_list	*current;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	current = lst;
	ret = NULL;
	while (current)
	{
		iter = ft_lstnew(f(current->content));
		if (iter == NULL)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		ft_lstadd_back(&ret, iter);
		current = current->next;
	}
	return (ret);
}
