/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handle_default_state.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:39:40 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/24 12:44:35 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	handle_default(t_lexer *lex)
{
	if (is_space(lex->input[lex->i]))
		handle_space(lex);
	else if (is_operador_shell(lex->input[lex->i]))
		handle_operador_state(lex);
	else if (lex->input[lex->i] == '\'')
		enter_single_quote(lex);
	else if (lex->input[lex->i] == '"')
		enter_double_quote(lex);
	else
		handle_word_char(lex, lex->input[lex->i]);
}

void static	handle_space(t_lexer *lex)
{
	finalize_word_if_needed(lex);
	lex->i++;
}

void static	handle_operador_state(t_lexer *lex)
{
	t_token_type	type;

	finalize_word_if_needed(lex);
	type = detect_operator(lex, lex->input[lex->i]);
	if (type == TOKEN_INVALID)
	{
		lex->error = 1;
		return ;
	}
	add_operador_token(lex, type);
}

void static	enter_single_quote(t_lexer *lex)
{
	lex->state == LEX_SINGLE_QUOTE;
	lex->i++;
}

void static	handle_word_char(t_lexer *lex, char c)
{
	buffer_add_char(lex, c);
	lex->i++;
}
