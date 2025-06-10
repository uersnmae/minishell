/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:43:40 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/07 14:18:23 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str_array(char **arr)
{
	size_t	index;

	index = 0;
	if (arr == NULL)
		return ;
	while (arr[index] != NULL)
		free(arr[index++]);
	free(arr);
}

void	free_str_list(t_list **lst)
{
	if (lst == NULL)
		return ;
	ft_lstclear(lst, free);
}

void	cleanup_array_and_list(char **arr, t_list **lst)
{
	free_str_array(arr);
	free_str_list(lst);
}

t_list	*str_array_to_list(char **arr)
{
	t_list	*lst;
	t_list	*node;
	size_t	index;
	char	*str;

	lst = NULL;
	index = 0;
	while (arr[index] != NULL)
	{
		str = ft_strdup(arr[index++]);
		if (str == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		node = ft_lstnew(str);
		if (node == NULL)
		{
			free(str);
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}

char	**list_to_str_array(t_list *lst)
{
	char	**arr;
	size_t	len;
	size_t	index;
	t_list	*cur;

	len = 0;
	cur = lst;
	while (cur != NULL)
	{
		len++;
		cur = cur->next;
	}
	arr = ft_calloc(len + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	cur = lst;
	index = 0;
	while (cur != NULL)
	{
		arr[index++] = ft_strdup((char *)cur->content);
		cur = cur->next;
	}
	return (arr);
}
