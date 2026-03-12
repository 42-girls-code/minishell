/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:05:53 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:23:15 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*handle_pipe(t_ast *left, t_token **tokens,
					t_token **err_token, t_token *pipe)
{
	t_ast	*right;
	t_ast	*node;

	right = parse_primary(tokens, err_token);
	if (!right)
	{
		if (err_token && !*err_token)
			*err_token = pipe;
		free_ast(left);
		return (NULL);
	}
	node = create_node(NODE_PIPE);
	if (!node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_pipeline(t_token **tokens, t_token **err_token)
{
	t_ast	*left;
	t_ast	*node;
	t_token	*pipe;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_primary(tokens, err_token);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		pipe = *tokens;
		*tokens = pipe->next;
		node = handle_pipe(left, tokens, err_token, pipe);
		if (!node)
			return (NULL);
		left = node;
	}
	return (left);
}
