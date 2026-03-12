/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:03:43 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:46:21 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirection(t_token_type type)
{
	if (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	add_arg(t_ast *node, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	while (node->args && node->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (node->args && node->args[i])
	{
		new_args[i] = node->args[i];
		i++;
	}
	new_args[i++] = ft_strdup(value);
	new_args[i] = NULL;
	free(node->args);
	node->args = new_args;
	return (1);
}

static int	validate_redirection(t_token *file, t_token **err_token)
{
	if (!file || file->type != TOKEN_WORD)
	{
		if (err_token && file && file->type != TOKEN_WORD)
			*err_token = file;
		else if (err_token)
			*err_token = NULL;
		return (0);
	}
	return (1);
}

static void	apply_redirection(t_ast *node, t_token *redir, t_token *file)
{
	if (redir->type == TOKEN_REDIR_IN)
	{
		free(node->infile);
		node->infile = ft_strdup(file->value);
	}
	else if (redir->type == TOKEN_REDIR_OUT)
	{
		free(node->outfile);
		node->outfile = ft_strdup(file->value);
		node->append = 0;
	}
	else if (redir->type == TOKEN_APPEND)
	{
		free(node->outfile);
		node->outfile = ft_strdup(file->value);
		node->append = 1;
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		free(node->heredoc_delim);
		node->heredoc_delim = ft_strdup(file->value);
	}
}

int	handle_redirection(t_ast *node, t_token **tokens,
		t_token **err_token)
{
	t_token	*redir;
	t_token	*file;

	redir = *tokens;
	file = redir->next;
	if (!validate_redirection(file, err_token))
		return (0);
	apply_redirection(node, redir, file);
	*tokens = file->next;
	return (1);
}
