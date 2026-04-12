/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:06:07 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 21:10:49 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"

// char	*expand_var_heredoc(char *line, t_minishell *shell)
// {
// 	t_lexer	expand_lex;
// 	char	*result;
// 	if (!line)
// 		return (NULL);
// 	init_lexer_buffer(&expand_lex);
// 	while (*line)
// 	{
// 		if (*line == '$')
// 			handler_expansion(&line, &expand_lex, shell);
// 		else
// 		{
// 			buffer_add_char(&expand_lex, *line);
// 			line++;
// 		}
// 	}
// 	result = ft_strdup(expand_lex.buffer);
// 	free(expand_lex.buffer);
// 	return (result);
// }

// void	run_heredoc_child(int write_fd, char *delimiter)
// {
// 	struct sigaction	sa;
// 	char				*line;

// 	sa.sa_handler = child_sigint_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			ft_putstr_fd("warning: here-document delimited by EOF\n", 2);
// 			exit(0);
// 		}
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			exit(0);
// 		}
// 		write(write_fd, line, ft_strlen(line));
// 		write(write_fd, "\n", 1);
// 		free(line);
// 	}
// }
