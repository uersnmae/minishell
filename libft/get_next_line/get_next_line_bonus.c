/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:47:49 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/28 10:58:05 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*ft_lstnew(int fd)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == (void *)0)
		return ((void *)0);
	node->fd = fd;
	node->str = NULL;
	node->next = (void *)0;
	return (node);
}

static t_list	*ft_lstfindfd(t_list **lst, int fd)
{
	t_list	*current;
	t_list	*prev;
	t_list	*new;

	current = (*lst);
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		prev = current;
		current = current->next;
	}
	new = ft_lstnew(fd);
	if (new == NULL)
		return (NULL);
	if (prev)
		prev->next = new;
	else
		(*lst) = new;
	return (new);
}

static void	ft_lstdel_node(t_list **lst, int fd)
{
	t_list	*current;
	t_list	*prev;

	if (lst == NULL || (*lst) == NULL)
		return ;
	current = (*lst);
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				(*lst) = current->next;
			free(current->str);
			current->str = NULL;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static char	*ft_extract_line(t_list *buf)
{
	size_t	index;
	char	*line;
	char	*temp;

	index = 0;
	while (buf->str[index] && buf->str[index] != '\n')
		index++;
	if (buf->str[index] == '\n')
		index++;
	line = ft_substr(buf->str, 0, index);
	temp = buf->str;
	buf->str = ft_substr(buf->str, index, ft_strlen(buf->str) - index);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_lstfindfd(&head, fd);
	if (buf == NULL)
		return (NULL);
	buf->str = ft_read_file(fd, buf->str);
	if (buf->str == NULL || *(buf->str) == '\0')
	{
		ft_lstdel_node(&head, fd);
		return (NULL);
	}
	line = ft_extract_line(buf);
	return (line);
}
