/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:07:09 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/05 21:33:55 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "libft.h"

# define WILDCARD_ERROR	-1

t_list	*expand_wildcard(const char *pattern);
t_list	*expand_wildcard_arguments(t_list *argv);

#endif
