/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:18:13 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/01 21:45:54 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*expand_var(char *arg, t_minishell *shell);
static void	expand_args(char **args, t_minishell *shell);
static void	expand_redirection(char **file, t_minishell *shell);

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

static char	*expand_var(char *arg, t_minishell *shell)
{
	char	*value;

	if (arg[0] != '$')
		return (ft_strdup(arg));
	if (!ft_strcmp(arg, "$?"))
		return (ft_itoa(shell->last_status));
	value = get_env_value(shell->env, arg + 1);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
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

static void	expand_redirection(char **file, t_minishell *shell)
{
	char	*new;

	new = expand_var(*file, shell);
	if (!new)
		new = ft_strdup("");
	free(*file);
	*file = new;
}
