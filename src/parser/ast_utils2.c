/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:51:10 by csuomins          #+#    #+#             */
/*   Updated: 2026/04/13 14:53:16 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_parse_error(t_token *err_token)
{
	if (err_token)
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			err_token->value);
	else
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
}

void	print_node_type(t_node_type type)
{
	if (type == NODE_COMMAND)
		printf("COMMAND");
	else if (type == NODE_PIPE)
		printf("PIPE");
	else if (type == NODE_AND)
		printf("AND");
	else if (type == NODE_OR)
		printf("OR");
}
