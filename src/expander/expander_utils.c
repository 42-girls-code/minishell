/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:58:56 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/12 15:55:52 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	init_lexer_buffer(t_lexer *lex)
{
	lex->capacity = 128;
	lex->buffer = malloc(lex->capacity);
	if (!lex->buffer)
		exit (EXIT_FAILURE);
	lex->buffer[0] = '\0';
	lex->buf_size = 0;
}

void	add_string_to_buffer(t_lexer *lex, char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		buffer_add_char(lex, str[i]);
		i++;
	}
}
