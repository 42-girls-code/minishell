/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:56:55 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/13 19:16:40 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "expander.h"
#include "heredoc.h"

static t_ast	*build_ast(char *line, t_minishell *shell, t_token **tokens);

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	handle_input(char *line, t_minishell *shell)
{
	t_ast	*root;
	t_token	*tokens;

	root = build_ast(line, shell, &tokens);
	if (!root)
		return ;
	expand_ast(root, shell);
	if (!prepare_heredocs(root, shell))
		shell->last_status = execute_ast(root, shell);
	free_ast(root);
	free_tokens(tokens);
	shell->active_ast = NULL;
	shell->active_tokens = NULL;
}

static t_ast	*build_ast(char *line, t_minishell *shell, t_token **tokens)
{
	t_token	*err_token;
	t_ast	*root;

	*tokens = lexer(line);
	shell->active_tokens = *tokens;
	if (!*tokens)
	{
		ft_putendl_fd(
			"minishell: unexpected EOF while looking for matching quote", 2);
		shell->active_tokens = NULL;
		return (NULL);
	}
	err_token = NULL;
	root = parse(*tokens, &err_token);
	shell->active_ast = root;
	if (!root)
	{
		print_parse_error(err_token);
		free_tokens(*tokens);
		shell->active_tokens = NULL;
	}
	return (root);
}
