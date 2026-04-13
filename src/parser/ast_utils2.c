/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:16:02 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/12 22:08:20 by cris_sky         ###   ########.fr       */
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

static void	print_one_redir(t_redir *r)
{
	if (r->type == TOKEN_REDIR_IN)
		printf(" < %s", r->file);
	else if (r->type == TOKEN_HEREDOC)
		printf(" << %s", r->file);
	else if (r->type == TOKEN_APPEND)
		printf(" >> %s", r->file);
	else
		printf(" > %s", r->file);
}

static void	print_redirections(t_ast *node)
{
	t_redir	*r;

	r = node->redirs;
	while (r)
	{
		print_one_redir(r);
		r = r->next;
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
