/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:41:51 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/12 14:57:32 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	is_valid_identifier(char *str);
static void	remove_env_key(t_envp **env_list, char *key);

int	builtin_unset(char **args, t_minishell *shell)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("unset: not a valid identifier: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("\n", 2);
			ret = 1;
		}
		else
			remove_env_key(&shell->env, args[i]);
		i++;
	}
	return (ret);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_key(t_envp **env_list, char *key)
{
	t_envp	*prev;
	t_envp	*curr;

	if (!env_list || !*env_list)
		return ;
	prev = NULL;
	curr = *env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
