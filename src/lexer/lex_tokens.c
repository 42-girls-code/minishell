/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:49:51 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/26 00:54:16 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_operador_token(t_lexer *lex, t_token_type type)
{
	char	*value;

	if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
	{
		value = ft_substr(lex->input, lex->i, 2);
		lex->i += 2;
	}
	else
	{
		value = ft_substr(lex->input, lex->i, 1);
		lex->i++;
	}
	add_token(lex, type, value);
	free(value);
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
		lex->tail = new;
	}
	else
	{
		lex->tail->next = new;
		lex->tail = new;
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

t_token_type	detect_operator(t_lexer *lex)
{
	if (lex->input[lex->i] && lex->input[lex->i + 1]
		&& lex->input[lex->i + 1] == lex->input[lex->i])
	{
		if (lex->input[lex->i] == '|')
			return (TOKEN_OR);
		if (lex->input[lex->i] == '<')
			return (TOKEN_HEREDOC);
		if (lex->input[lex->i] == '>')
			return (TOKEN_APPEND);
		if (lex->input[lex->i] == '&')
			return (TOKEN_AND);
	}
	if (lex->input[lex->i] == '|')
		return (TOKEN_PIPE);
	if (lex->input[lex->i] == '<')
		return (TOKEN_REDIR_IN);
	if (lex->input[lex->i] == '>')
		return (TOKEN_REDIR_OUT);
	if (lex->input[lex->i] == '(')
		return (TOKEN_L_PAREN);
	if (lex->input[lex->i] == ')')
		return (TOKEN_R_PAREN);
	return (TOKEN_INVALID);
}
