/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:26:49 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/12 15:46:05 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "expander.h"
#include <readline/readline.h>

static void	finish_heredoc(char *line, char *n_delim, int fd);
static void	process_heredoc_line(char *line, int fd, int expand,
				t_minishell *shell);

void	run_heredoc_child(int write_fd, char *delim, t_minishell *shell)
{
	char	*line;
	char	*n_delim;
	char	*tmp_delim;
	int		expand;

	expand = (ft_strchr(delim, '\'') == NULL
			&& ft_strchr(delim, '\"') == NULL);
	tmp_delim = ft_strdup(delim);
	n_delim = expand_var(tmp_delim, shell);
	free(tmp_delim);
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, n_delim) == 0)
		{
			if (!line)
				ft_putstr_fd("warning: here-document delimited by EOF\n", 2);
			break ;
		}
		process_heredoc_line(line, write_fd, expand, shell);
		free(line);
	}
	finish_heredoc(line, n_delim, write_fd);
}

static void	process_heredoc_line(char *line, int fd, int expand,
	t_minishell *shell)
{
	char	*expanded;

	if (expand)
		expanded = expand_var_heredoc(line, shell);
	else
		expanded = ft_strdup(line);
	if (expanded)
	{
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
}

static void	finish_heredoc(char *line, char *n_delim, int fd)
{
	if (line)
		free(line);
	if (n_delim)
		free(n_delim);
	close(fd);
	exit(0);
}

char	*expand_var_heredoc(char *line, t_minishell *shell)
{
	t_lexer	expand_lex;
	char	*result;

	if (!line)
		return (NULL);
	init_lexer_buffer(&expand_lex);
	while (*line)
	{
		if (*line == '$')
			handler_expansion(&line, &expand_lex, shell);
		else
		{
			buffer_add_char(&expand_lex, *line);
			line++;
		}
	}
	result = ft_strdup(expand_lex.buffer);
	free(expand_lex.buffer);
	return (result);
}
