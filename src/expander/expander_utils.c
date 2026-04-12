/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:58:56 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 21:26:31 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	handle_quotes(char c, int *state, t_lexer *lex);
static void	add_string_to_buffer(t_lexer *lex, char *str);

char	*expand_var(char *arg, t_minishell *shell)
{
	t_lexer	expand_lex;
	int		state;
	char	*result;

	if (!arg)
		return (NULL);
	init_lexer_buffer(&expand_lex);
	state = DEFAULT;
	while (*arg)
	{
		if (*arg == '\'' || *arg == '\"')
			handle_quotes(*arg++, &state, &expand_lex);
		else if (*arg == '$' && state != S_QUOTE)
			handler_expansion(&arg, &expand_lex, shell);
		else
		{
			buffer_add_char(&expand_lex, *arg);
			arg++;
		}
	}
	result = ft_strdup(expand_lex.buffer);
	free(expand_lex.buffer);
	return (result);
}

void	init_lexer_buffer(t_lexer *lex)
{
	lex->capacity = 128;
	lex->buffer = malloc(lex->capacity);
	if (!lex->buffer)
		exit (EXIT_FAILURE);
	lex->buffer[0] = '\0';
	lex->buf_size = 0;
}

static void	handle_quotes(char c, int *state, t_lexer *lex)
{
	if (c == '\'')
	{
		if (*state == DEFAULT)
			*state = S_QUOTE;
		else if (*state == S_QUOTE)
			*state = DEFAULT;
		else
			buffer_add_char(lex, c);
	}
	else if (c == '\"')
	{
		if (*state == DEFAULT)
			*state = D_QUOTE;
		else if (*state == D_QUOTE)
			*state = DEFAULT;
		else
			buffer_add_char(lex, c);
	}
}

void	handler_expansion(char **arg, t_lexer *lex, t_minishell *shell)
{
	char	key[256];
	char	*value;
	int		i;

	(*arg)++;
	if (**arg == '?')
	{
		value = ft_itoa(shell->last_status);
		add_string_to_buffer(lex, value);
		free(value);
		(*arg)++;
	}
	else if (ft_isalnum(**arg) || **arg == '_')
	{
		i = 0;
		while ((ft_isalnum(**arg) || **arg == '_') && i < 255)
			key[i++] = *(*arg)++;
		key[i] = '\0';
		value = get_env_value(shell->env, key);
		if (value)
			add_string_to_buffer(lex, value);
	}
	else
	{
		buffer_add_char(lex, '$');
		(*arg)++;
	}
}

static void	add_string_to_buffer(t_lexer *lex, char *str)
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
