/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:22:08 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/27 22:31:37 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_table.h"
#include "tokenizer.h"
#include "ast.h"
#include "signal_handler.h"
#include "input.h"
#include "minishell.h"

#define STR_TK_ERROR	"syntax error near unexpected token "

static void	free_cmd_line(t_shell *shell)
{
	free_ast_node(shell->root_node);
	shell->root_node = NULL;
	free(shell->line);
	shell->line = NULL;
}

static int	free_line_err(t_shell *shell, int status)
{
	free_cmd_line(shell);
	free_tokens(&shell->tokens);
	shell->last_status = status;
	return (shell->last_status);
}

static int	parse_cmd(t_shell *shell)
{
	t_token	*tokens;

	shell->tokens = NULL;
	shell->line = get_input();
	if (!shell->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (1);
	}
	if (!tokenize(shell->line, &tokens))
		return (free_line_err(shell, 2));
	shell->tokens = tokens;
	shell->root_node = ast_create(&tokens);
	if (shell->root_node == NULL)
	{
		return (free_line_err(shell, 2));
	}
	return (0);
}

int	run_cmd_line(t_shell *shell)
{
	int	result;

	while (shell->running)
	{
		init_signals(sigint_handler);
		result = parse_cmd(shell);
		if (result == 2)
			continue ;
		else if (result == 1)
			break ;
		shell->curr_node = shell->root_node;
		run_ast(shell);
		free_cmd_line(shell);
	}
	env_table_free(shell->env);
	rl_clear_history();
	close(shell->stdin);
	close(shell->stdout);
	free(shell->base_dir);
	return (shell->last_status);
}
