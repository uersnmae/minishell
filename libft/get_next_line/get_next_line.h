/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:49:01 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/19 14:14:41 by kim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	gnl_strlen(const char *str);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_read_file(int fd, char *buffer);
char	*get_next_line(int fd);

#endif
