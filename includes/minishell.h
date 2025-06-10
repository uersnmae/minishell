/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:01:53 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/18 15:49:22 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env_table.h"
# include "ast.h"
# include "command_structs.h"

typedef struct s_shell
{
	t_token			*tokens;
	t_env_table		*env;
	t_ast_node		*root_node;
	t_ast_node		*curr_node;
	t_job			*jobs;
	int				last_status;
	int				running;
	int				stdin;
	int				stdout;
	int				subshell_flag;
	char			*base_dir;
	char			*line;
	char			**envp;
}	t_shell;

void	cleanup(char **path, t_shell *shell);
int		error_status(char *msg, char *detail, int err_val, bool flag);
void	pipeline_run_ast(t_ast_node	*cmd, t_shell *shell);
int		run_ast(t_shell *shell);
int		run_cmd_line(t_shell *shell);

#endif
