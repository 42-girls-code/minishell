/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handle_default_state.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:39:40 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/26 00:53:03 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	handle_operador_state(t_lexer *lex);
static void	enter_single_quote(t_lexer *lex);
static void	enter_double_quote(t_lexer *lex);
static void	handle_word_char(t_lexer *lex, char c);

void	handle_default(t_lexer *lex)
{
	if (is_space(lex->input[lex->i]))
	{
		finalize_word_if_needed(lex);
		lex->i++;
	}
	else if (is_operador_shell(lex->input[lex->i]))
		handle_operador_state(lex);
	else if (lex->input[lex->i] == '\'')
		enter_single_quote(lex);
	else if (lex->input[lex->i] == '"')
		enter_double_quote(lex);
	else
		handle_word_char(lex, lex->input[lex->i]);
}

static void	handle_operador_state(t_lexer *lex)
{
	t_token_type	type;

	finalize_word_if_needed(lex);
	type = detect_operator(lex);
	if (type == TOKEN_INVALID)
	{
		lex->error = 1;
		return ;
	}
	add_operador_token(lex, type);
}

static void	enter_single_quote(t_lexer *lex)
{
	lex->state = LEX_SINGLE_QUOTE;
	lex->word_started = 1;
	lex->i++;
}

static void	enter_double_quote(t_lexer *lex)
{
	lex->state = LEX_DOUBLE_QUOTE;
	lex->word_started = 1;
	lex->i++;
}

static void	handle_word_char(t_lexer *lex, char c)
{
	lex->word_started = 1;
	buffer_add_char(lex, c);
	lex->i++;
}
