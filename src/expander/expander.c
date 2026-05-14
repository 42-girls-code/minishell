/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:18:13 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/12 20:59:12 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_args(char **args, t_minishell *shell);
static void	expand_redirs(t_redir *redirs, t_minishell *shell);

void	expand_ast(t_ast *root, t_minishell *shell)
{
	if (!root)
		return ;
	if (root->type == NODE_COMMAND)
	{
		expand_args(root->args, shell);
		expand_redirs(root->redirs, shell);
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

static void	expand_redirs(t_redir *redirs, t_minishell *shell)
{
	char	*new;

	while (redirs)
	{
		if (redirs->type != TOKEN_HEREDOC)
		{
			new = expand_var(redirs->file, shell);
			if (!new)
				new = ft_strdup("");
			free(redirs->file);
			redirs->file = new;
		}
		redirs = redirs->next;
	}
}
