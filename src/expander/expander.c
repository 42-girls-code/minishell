/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:18:13 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 13:58:32 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	expand_args(char **args, t_minishell *shell);
static char	*expand_var(char *arg, t_minishell *shell);
static void	handler_dollar_expansion(char **arg, t_lexer *lex,
	t_minishell *shell);
static void	add_string_to_buffer(t_lexer *lex, char *str);
static void	expand_redirection(char **file, t_minishell *shell);
static void	init_lexer_buffer(t_lexer *lex);

void	expand_ast(t_ast *root, t_minishell *shell)
{
	if (!root)
		return ;
	if (root->type == NODE_COMMAND)
	{
		expand_args(root->args, shell);
		if (root->infile)
			expand_redirection(&root->infile, shell);
		if (root->outfile)
			expand_redirection(&root->outfile, shell);
	}
	expand_ast(root->left, shell);
	expand_ast(root->right, shell);
}

static void	expand_args(char **args, t_minishell *shell)
{
	int		i;
	char	*new;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		new = expand_var(args[i], shell);
		// if (!new) passar responsabilidade para o executor
		// 	new = ft_strdup("");
		free(args[i]);
		args[i] = new;
		i++;
	}
}

static char	*expand_var(char *arg, t_minishell *shell)
{
	t_lexer	expand_lex;
	int		state;
	char	*result;

	if (!arg)
		return (NULL);
	init_lexer_buffer(&expand_lex);
	state  = DEFAULT;
	while (*arg)
	{
		if (*arg == '\'' && state == DEFAULT)
		{
			state = S_QUOTE;
			arg++;
		}
		else if (*arg == '\'' && state == S_QUOTE)
		{
			state = DEFAULT;
			arg++;
		}
		else if (*arg == '\"' && state == DEFAULT)
		{
			state = D_QUOTE;
			arg++;
		}
		else if (*arg == '\"' && state == D_QUOTE)
		{
			state = DEFAULT;
			arg++;
		}
		else if (*arg == '$' && state != S_QUOTE)
			handler_dollar_expansion(&arg, &expand_lex, shell);
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

static void	handler_dollar_expansion(char **arg, t_lexer *lex,
	t_minishell *shell)
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
		buffer_add_char(lex, '$');
}

static void	init_lexer_buffer(t_lexer *lex)
{
	lex->capacity = 128;
	lex->buffer = malloc(lex->capacity);
	if (!lex->buffer)
		exit (EXIT_FAILURE);
	lex->buffer[0] = '\0';
	lex->buf_size = 0;
}

static void	expand_redirection(char **file, t_minishell *shell)
{
	char	*new;

	new = expand_var(*file, shell);
	if (!new)
		new = ft_strdup("");
	free(*file);
	*file = new;
}

static void	add_string_to_buffer(t_lexer *lex, char *str)
{
	int	i;

	if (!str)
		return;
	i = 0;
	while (str[i])
	{
		buffer_add_char(lex, str[i]);
		i++;
	}
}
