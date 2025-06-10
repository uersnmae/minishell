/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:11:35 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/16 14:50:16 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_table.h"

t_env_table	*env_init(char **envp)
{
	return (env_table_create(211, envp));
}

void	env_free_envp(char **envp)
{
	size_t	i;

	i = 0;
	while (envp && envp[i])
		free(envp[i++]);
	free(envp);
}
