/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:18:45 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/24 15:19:06 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_operador_shell(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == '(' || c == ')')
		return (1);
	else
		return (0);
}

void	buffer_add_char(t_lexer *lex, char c)
{
	lex->buffer[lex->buf_size] = c;
	lex->buf_size++;
	lex->buffer[lex->buf_size] = '\0';
}

void	finalize_word_if_needed(t_lexer *lex)
{
	if (lex->word_started)
	{
		add_token(lex, TOKEN_WORD, lex->buffer);
		lex->buf_size = 0;
		lex->buffer[0] = '\0';
		lex->word_started = 0;
	}
}
