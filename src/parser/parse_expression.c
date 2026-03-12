/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:06:37 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:22:49 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*handle_logical_op(t_ast *left, t_token **tokens,
					t_token **err_token, t_token *op)
{
	t_ast	*right;
	t_ast	*node;

	right = parse_pipeline(tokens, err_token);
	if (!right)
	{
		if (err_token && !*err_token)
			*err_token = op;
		free_ast(left);
		return (NULL);
	}
	if (op->type == TOKEN_AND)
		node = create_node(NODE_AND);
	else
		node = create_node(NODE_OR);
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

t_ast	*parse_expression(t_token **tokens, t_token **err_token)
{
	t_ast		*left;
	t_ast		*node;
	t_token		*op;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_pipeline(tokens, err_token);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		op = *tokens;
		*tokens = op->next;
		node = handle_logical_op(left, tokens, err_token, op);
		if (!node)
			return (NULL);
		left = node;
	}
	return (left);
}
