/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:48 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/03 14:02:48 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_ARRAY_LIST_H
# define STR_ARRAY_LIST_H

# include "libft.h"

void	free_str_array(char **arr);
void	free_str_list(t_list **lst);
void	*cleanup_array_and_list(char **arr, t_list **lst);
t_list	*str_array_to_list(char **arr);
char	**list_to_str_array(t_list *lst);

#endif
