/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:04:45 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 13:53:24 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_primary(t_token **tokens, t_token **err_token)
{
	t_ast	*node;

	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_L_PAREN)
	{
		*tokens = (*tokens)->next;
		node = parse_expression(tokens, err_token);
		if (!node)
			return (NULL);
		if (!*tokens || (*tokens)->type != TOKEN_R_PAREN)
		{
			if (err_token)
				*err_token = *tokens;
			free_ast(node);
			return (NULL);
		}
		*tokens = (*tokens)->next;
		return (node);
	}
	return (parse_command(tokens, err_token));
}
