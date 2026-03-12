/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:27:19 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:27:54 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	handle_command_token(t_ast *node, t_token **tokens,
		t_token **err_token)
{
	if ((*tokens)->type == TOKEN_WORD)
	{
		if (!add_arg(node, (*tokens)->value))
			return (0);
		*tokens = (*tokens)->next;
	}
	else
	{
		if (!handle_redirection(node, tokens, err_token))
			return (0);
	}
	return (1);
}

t_ast	*parse_command(t_token **tokens, t_token **err_token)
{
	t_ast	*node;

	if (!tokens || !*tokens)
		return (NULL);
	node = create_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_WORD
			|| is_redirection((*tokens)->type)))
	{
		if (!handle_command_token(node, tokens, err_token))
		{
			free_ast(node);
			return (NULL);
		}
	}
	return (node);
}
