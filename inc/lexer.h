/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:54:23 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/26 00:29:30 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN, // <
	TOKEN_REDIR_OUT, // >
	TOKEN_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_L_PAREN,
	TOKEN_R_PAREN,
	TOKEN_INVALID,
}	t_token_type;

typedef enum e_lex_state
{
	LEX_DEFAULT,
	LEX_SINGLE_QUOTE,
	LEX_DOUBLE_QUOTE,
}	t_lex_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	int			i;
	t_lex_state	state;
	char		*buffer;
	size_t		buf_size;
	size_t		word_started;
	t_token		*tokens;
	t_token		*tail;
	int			error;
}	t_lexer;

//lex_util.c
int				is_space(char c);
int				is_operador_shell(char c);
void			buffer_add_char(t_lexer *lex, char c);
void			finalize_word_if_needed(t_lexer *lex);

//lex_default_state
void			handle_default(t_lexer *lex);

//lex_tokens
void			add_operador_token(t_lexer *lex, t_token_type type);
void			add_token(t_lexer *lex, t_token_type type, char *buffer);
t_token			*new_token(t_token_type type, char *buffer);
void			free_tokens(t_token *tokens);
t_token_type	detect_operator(t_lexer *lex);

//lexer.c
t_token			*lexer(char *input);
void			init_lexer(t_lexer *lex, char *input);
void			finalize_word_if_needed(t_lexer *lex);
void			handle_double_quote(t_lexer *lex);
void			handle_single_quote(t_lexer *lex);

#endif
