/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:47:35 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/18 13:41:07 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

void	sigint_handler(int signo);
void	sigint_handler_heredoc(int signo);
void	init_signals(void (*sig_handler)(int signo));
void	set_child_signal(void);
void	set_parent_signal(void);

#endif
