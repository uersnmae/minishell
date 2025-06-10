/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:54:30 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/04 11:49:01 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"
# include "signal_handler.h"

char	*get_input(void);
void	fail_get_input(void);
int		is_escaped(const char *start, const char *s);
int		is_only_ws(const char *str);

#endif
