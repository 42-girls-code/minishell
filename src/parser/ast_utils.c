/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:55:29 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:49:34 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

t_ast	*create_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc_delim = NULL;
	return (node);
}

static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	free_args(ast->args);
	if (ast->infile)
		free(ast->infile);
	if (ast->outfile)
		free(ast->outfile);
	if (ast->heredoc_delim)
		free(ast->heredoc_delim);
	free(ast);
}

void	print_indent(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		printf("    ");
		i++;
	}
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
