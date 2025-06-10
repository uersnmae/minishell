/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:51:34 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/17 15:53:37 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_STRUCTS_H
# define COMMAND_STRUCTS_H

# include <stdbool.h>
# include "tokenizer.h"

typedef enum e_connector
{
	CONN_NONE,
	CONN_AND,
	CONN_OR
}	t_connector;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				fd;
	bool			ambiguous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	t_token				*command_tokens;
	t_redir				*redirs;
	char				**argv;
	struct s_command	*next;
}	t_command;

typedef struct s_job
{
	t_connector		conn;
	t_command		*pipeline;
	struct s_job	*next;
}	t_job;

#endif
