/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:35:25 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/12 20:57:25 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	t_redir			*redirs;
	int				heredoc_fd;
}	t_ast;

t_ast	*parse(t_token *tokens, t_token **err_token);
void	free_ast(t_ast *ast);
t_ast	*create_node(t_node_type type);
void	print_ast(t_ast *ast, int level);
t_ast	*parse_expression(t_token **tokens, t_token **err_token);
t_ast	*parse_pipeline(t_token **tokens, t_token **err_token);
t_ast	*parse_primary(t_token **tokens, t_token **err_token);
void	print_command(t_ast *node);
void	print_parse_error(t_token *err_token);
t_ast	*parse_command(t_token **tokens, t_token **err_token);
int		is_redirection(t_token_type type);
int		add_arg(t_ast *node, char *value);
int		handle_redirection(t_ast *node, t_token **tokens,
			t_token **err_token);
void	print_indent(int level);
void	print_node_type(t_node_type type);
void	free_redirs(t_redir *redirs);
t_redir	*new_redir(t_token_type type, char *file);

#endif
