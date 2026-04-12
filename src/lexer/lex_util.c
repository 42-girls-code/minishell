/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:18:45 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 11:11:46 by ingrid           ###   ########.fr       */
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
	char	*new_buffer;
	size_t	new_cap;

	if (lex->buf_size + 2 >= lex->capacity)
	{
		new_cap = lex->capacity * 2;
		new_buffer = malloc(new_cap);
		if (!new_buffer)
		{
			lex->error = 1;
			return ;
		}
		ft_memcpy(new_buffer, lex->buffer, lex->buf_size);
		new_buffer[lex->buf_size] = '\0';
		free(lex->buffer);
		lex->buffer = new_buffer;
		lex->capacity = new_cap;
	}
	lex->buffer[lex->buf_size++] = c;
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
