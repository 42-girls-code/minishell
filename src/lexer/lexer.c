/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:00:41 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/27 13:09:55 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *input)
{
	t_lexer			lex;

	init_lexer(&lex, input);
	while (lex.input[lex.i] && !lex.error)
	{
		if (lex.state == LEX_DEFAULT)
			handle_default(&lex);
		else if (lex.state == LEX_SINGLE_QUOTE)
			handle_single_quote(&lex);
		else if (lex.state == LEX_DOUBLE_QUOTE)
			handle_double_quote(&lex);
	}
	if (lex.error)
	{
		free_tokens(lex.tokens);
		free(lex.buffer);
		return (NULL);
	}
	finalize_word_if_needed(&lex);
	free(lex.buffer);
	return (lex.tokens);
}

void	init_lexer(t_lexer *lex, char *input)
{
	lex->input = input;
	lex->i = 0;
	lex->state = LEX_DEFAULT;
	lex->buffer = malloc(ft_strlen(lex->input) + 1);
	if (!lex->buffer)
		exit (EXIT_FAILURE);
	lex->buffer[0] = '\0';
	lex->buf_size = 0;
	lex->word_started = 0;
	lex->tokens = NULL;
	lex->tail = NULL;
	lex->error = 0;
}

void	handle_double_quote(t_lexer *lex)
{
	while (lex->input[lex->i] && lex->input[lex->i] != '"')
	{
		buffer_add_char(lex, lex->input[lex->i]);
		lex->i++;
	}
	if (lex->input[lex->i] == '"')
		lex->i++;
	else
		lex->error = 1;
	lex->state = LEX_DEFAULT;
}

void	handle_single_quote(t_lexer *lex)
{
	while (lex->input[lex->i] && lex->input[lex->i] != '\'')
	{
		buffer_add_char(lex, lex->input[lex->i]);
		lex->i++;
	}
	if (lex->input[lex->i] == '\'')
		lex->i++;
	else
		lex->error = 1;
	lex->state = LEX_DEFAULT;
}
