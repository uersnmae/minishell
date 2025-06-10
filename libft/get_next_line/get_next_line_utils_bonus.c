/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:24:36 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/19 14:28:18 by kim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	len;
	char	*pstr;

	len = 0;
	pstr = (char *)str;
	while (*(pstr++))
		len++;
	return (len);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	total_len;
	size_t	index;
	size_t	jndex;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	total_len = gnl_strlen(s1) + gnl_strlen(s2);
	str = (char *)malloc((total_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (*(s1 + index))
	{
		*(str + index) = *(s1 + index);
		index++;
	}
	jndex = 0;
	while (*(s2 + jndex))
		*(str + index++) = *(s2 + jndex++);
	*(str + index) = '\0';
	return (str);
}

char	*gnl_strchr(const char *s, int c)
{
	char	*ps;

	if (s == NULL)
		return (NULL);
	ps = (char *)s;
	while (*ps)
	{
		if (*ps == (char)c)
			return (ps);
		ps++;
	}
	if (*ps == '\0' && c == 0)
		return (ps);
	return (0);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	index;

	if (s == NULL)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start >= s_len)
	{
		str = (char *)malloc(1);
		if (str == NULL)
			return (NULL);
		*str = 0;
		return (str);
	}
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < len && s[start])
		str[index++] = s[start++];
	str[index] = '\0';
	return (str);
}

char	*gnl_read_file(int fd, char *buffer)
{
	char	*read_buf;
	char	*temp;
	ssize_t	bytes_read;

	read_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buf == NULL)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buf);
			free(buffer);
			return (NULL);
		}
		*(read_buf + bytes_read) = '\0';
		temp = buffer;
		buffer = gnl_strjoin(buffer, read_buf);
		free(temp);
	}
	free(read_buf);
	return (buffer);
}
