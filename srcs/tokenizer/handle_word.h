/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:10 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/08 14:48:07 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_WORD_H
# define HANDLE_WORD_H

# include "tokenizer.h"

int		is_boundary(char c);
void	append_token(t_token **head, t_token **tail,
			const char *start, size_t raw_len);

#endif
