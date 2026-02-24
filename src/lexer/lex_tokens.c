/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:49:51 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/24 12:53:49 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_operador_token(t_lexer *lex, t_token_type type)
{
	add_token(lex, type, NULL);
	if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
		lex->i += 2;
	else
		lex->i++;
}

void	add_token(t_lexer *lex, t_token_type type, char *buffer)
{
	t_token	*new;

	new = new_token(type, buffer);
	if (!new)
		return ;
	if (!lex->tokens)
	{
		lex->tokens = new;
		lex->last = new;
	}
	else
	{
		lex->last->next = new;
		lex->last = new;
	}
}

t_token	*new_token(t_token_type type, char *buffer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(buffer);
	token->next = NULL;
	return (token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_token_type	detect_operator(t_lexer *lex, char c)
{
	char	next;

	next = lex->input[lex->i + 1];
	if (next == c)
	{
		if (c == '|')
			return (TOKEN_OR);
		if (c == '<')
			return (TOKEN_HEREDOC);
		if (c == '>')
			return (TOKEN_APPEND);
		if (c == '&')
			return (TOKEN_AND);
	}
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<')
		return (TOKEN_REDIR_IN);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	if (c == '(')
		return (TOKEN_L_PAREN);
	if (c == ')')
		return (TOKEN_R_PAREN);
	return (TOKEN_INVALID);
}
