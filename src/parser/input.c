/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:56:55 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/24 15:04:52 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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

void	handle_input(char *line)
{
	t_token	*tokens;
	t_token	*err_token;
	t_ast	*root;

	tokens = lexer(line);
	if (!tokens)
	{
		ft_putendl_fd(
			"minishell: unexpected EOF while looking for matching quote", 2);
		return ;
	}
	err_token = NULL;
	root = parse(tokens, &err_token);
	if (!root)
	{
		print_parse_error(err_token);
		free_tokens(tokens);
		return ;
	}
	free_ast(root);
	free_tokens(tokens);
}
