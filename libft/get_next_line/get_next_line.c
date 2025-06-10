/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:47:49 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/19 14:15:21 by kim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	char		*temp;
	size_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = gnl_read_file(fd, buf);
	if (buf == NULL || *buf == '\0')
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	index = 0;
	while (*(buf + index) && *(buf + index) != '\n')
		index++;
	if (*(buf + index) == '\n')
		index++;
	line = gnl_substr(buf, 0, index);
	temp = buf;
	buf = gnl_substr(buf, index, gnl_strlen(buf) - index);
	free(temp);
	return (line);
}
