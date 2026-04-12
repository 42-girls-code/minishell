/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:52:45 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/12 18:51:41 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	handle_quotes(char c, int *state, t_lexer *lex);
static void	expand_exit_status(t_lexer *lex, t_minishell *shell, char **arg);

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

static void	expand_exit_status(t_lexer *lex, t_minishell *shell, char **arg)
{
	char	*value;

	value = ft_itoa(shell->last_status);
	add_string_to_buffer(lex, value);
	free(value);
	(*arg)++;
}

void	handler_expansion(char **arg, t_lexer *lex, t_minishell *shell)
{
	char	key[256];
	char	*value;
	int		i;

	(*arg)++;
	if (**arg == '?')
		expand_exit_status(lex, shell, arg);
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
		buffer_add_char(lex, '$');
}
