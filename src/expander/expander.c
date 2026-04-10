/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:18:13 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/10 18:22:40 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*expand_var(char *arg, t_minishell *shell);
static void	expand_args(char **args, t_minishell *shell);
static void	expand_redirection(char **file, t_minishell *shell);
static char	*join_and_free(char *s1, char *s2);

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

	i = 0;
	while (args[i])
	{
		new = expand_var(args[i], shell);
		if (!new)
			new = ft_strdup("");
		free(args[i]);
		args[i] = new;
		i++;
	}
}

static char	*expand_var(char *arg, t_minishell *shell)
{
	char	*new_str;
	char	*tmp;
	char	key[256];
	char	*value;
	int		i;
	char	c[2];

	new_str = ft_strdup("");
	while (*arg)
	{
		if (*arg == '$')
		{
			arg++;
			if (*arg == '?')
			{
				tmp = ft_itoa(shell->last_status);
				arg++;
			}
			else
			{
				i = 0;
				while ((ft_isalnum(*arg) || *arg == '_') && i < 255)
					key[i++] = *arg++;
				key[i] = '\0';
				value = get_env_value(shell->env, key);
				if (!value)
					tmp = ft_strdup("");
				else
					tmp = ft_strdup(value);
			}
			if (!tmp)
			{
				free(new_str);
				return (NULL);
			}
			new_str = join_and_free(new_str, tmp);
			free(tmp);
			if (!new_str)
				return (NULL);
		}
		else
		{
			c[0] = *arg;
			c[1] = '\0';
			new_str = join_and_free(new_str, c);
			if (!new_str)
				return (NULL);
			arg++;
		}
	}
	return (new_str);
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

static char	*join_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}
