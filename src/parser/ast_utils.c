/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:55:29 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/12 21:03:48 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

t_redir	*new_redir(t_token_type type, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	r->next = NULL;
	return (r);
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free(tmp->file);
		free(tmp);
	}
}

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
	node->redirs = NULL;
	node->heredoc_fd = -1;
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
	free_redirs(ast->redirs);
	if (ast->heredoc_fd != -1)
		close(ast->heredoc_fd);
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