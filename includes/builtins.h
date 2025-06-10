/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:45:00 by hakslee           #+#    #+#             */
/*   Updated: 2025/05/16 13:40:53 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include "minishell.h"
# include "ast.h"

int		is_builtin(char *cmd);
int		exec_builtin(char **argv, t_shell *shell);

int		builtin_echo(char **argv);
int		builtin_pwd(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);

char	**parse_path(char *cmd, t_shell *shell);
char	**tokens_to_argv(t_token *tok);
void	free_path(char **paths);
char	*find_executable(const char *cmd, char **paths);
char	*join_path(const char *dir, const char *cmd);

int		is_numeric(const char *s);
long	convert_to_long(const char *num, int sign);

#endif
