/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:16:02 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/09 14:43:54 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_args(t_ast *node)
{
	int	i;

	if (!node->args)
		return ;
	printf(" [");
	i = 0;
	while (node->args[i])
	{
		printf("%s", node->args[i]);
		if (node->args[i + 1])
			printf(" ");
		i++;
	}
	printf("]");
}

static void	print_redirections(t_ast *node)
{
	if (node->infile)
		printf(" < %s", node->infile);
	if (node->heredoc_delim)
		printf(" << %s", node->heredoc_delim);
	if (node->outfile)
	{
		if (node->append)
			printf(" >> %s", node->outfile);
		else
			printf(" > %s", node->outfile);
	}
}

void	print_command(t_ast *node)
{
	if (!node)
		return ;
	print_args(node);
	print_redirections(node);
}

void	print_ast(t_ast *ast, int level)
{
	if (!ast)
		return ;
	print_indent(level);
	print_node_type(ast->type);
	if (ast->type == NODE_COMMAND)
		print_command(ast);
	printf("\n");
	print_ast(ast->left, level + 1);
	print_ast(ast->right, level + 1);
}

void	print_parse_error(t_token *err_token)
{
	if (err_token)
		ft_printf("minishell: syntax error near unexpected token `%s'\n",
			err_token->value);
	else
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
}
