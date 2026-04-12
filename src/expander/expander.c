/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:18:13 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 19:01:49 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
