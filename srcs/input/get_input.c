/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:45:48 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/07 14:13:52 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*get_input(void)
{
	char	*line;
	char	*complete;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			return (NULL);
		complete = line;
		while (*line && ft_isspace(*line))
			line++;
		if (*line == '\0')
			continue ;
		add_history(complete);
		return (complete);
	}
}
