/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:20:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/05/28 18:24:03 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>

#include "libft.h"
#include "expansion.h"
#include "tokenizer.h"
#include "signal_handler.h"
#include "minishell.h"

static char	*expand_heredoc_line(const char *in, t_shell *shell)
{
	size_t	i;
	char	*res;
	char	*seg;
	char	*tmp;

	res = ft_strdup("");
	if (!res)
		exit(EXIT_FAILURE);
	i = 0;
	while (in[i])
	{
		if (in[i] == '$')
			seg = sub_var(in + i, &i, shell);
		else
		{
			seg = ft_substr(in + i++, 0, 1);
			if (!seg)
				exit(EXIT_FAILURE);
		}
		tmp = ft_strjoin(res, seg);
		free(res);
		free(seg);
		res = tmp;
	}
	return (res);
}

static char	*prepare_delimiter(const char *raw, bool *quoted)
{
	char	*delim;

	*quoted = false;
	if (ft_strchr(raw, '\''))
		*quoted = true;
	delim = ft_strtrim(raw, "'\"");
	return (delim);
}

static int	delimited_eof(char *delim, int wfd, t_shell *shell)
{
	const int	fd = STDERR_FILENO;

	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd("warning: here-document delimited by end-of-file", fd);
	ft_putstr_fd("(wanted ", fd);
	ft_putstr_fd(delim, fd);
	free(delim);
	close(wfd);
	cleanup(NULL, shell);
	ft_putendl_fd(")", fd);
	return (fd);
}

static void	read_heredoc_body(char *delim, bool quoted, int wfd, t_shell *shell)
{
	char	*line;
	char	*out;

	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(delimited_eof(delim, wfd, shell));
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (!quoted)
		{
			out = expand_heredoc_line(line, shell);
			ft_putendl_fd(out, wfd);
			free(out);
		}
		else
			ft_putendl_fd(line, wfd);
		free(line);
	}
}

void	exec_heredoc_child(char *raw_delim, int pipefd[2], t_shell *shell)
{
	bool	quoted;
	char	*delim;

	init_signals(sigint_handler_heredoc);
	close(shell->stdin);
	close(shell->stdout);
	close(pipefd[0]);
	delim = prepare_delimiter(raw_delim, &quoted);
	free(raw_delim);
	read_heredoc_body(delim, quoted, pipefd[1], shell);
	free(delim);
	close(pipefd[1]);
	cleanup(NULL, shell);
	exit(EXIT_SUCCESS);
}
