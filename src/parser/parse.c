/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:18:50 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:48:11 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse(t_token *tokens, t_token **err_token)
{
	t_ast	*root;
	t_token	*current;

	if (err_token)
		*err_token = NULL;
	if (!tokens)
		return (NULL);
	current = tokens;
	root = parse_expression(&current, err_token);
	if (!root)
		return (NULL);
	if (current != NULL)
	{
		if (err_token)
			*err_token = current;
		free_ast(root);
		return (NULL);
	}
	return (root);
}
