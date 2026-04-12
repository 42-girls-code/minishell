/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 22:04:35 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/12 18:34:41 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*new_env_node(char *envp)
{
	char	**split_result;
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	split_result = ft_split(envp, '=');
	if (!split_result)
	{
		free(node);
		return (NULL);
	}
	node->key = ft_strdup(split_result[0]);
	if (split_result[1])
		node->value = ft_strdup(split_result[1]);
	else
		node->value = ft_strdup("");
	node->next = NULL;
	free_split(split_result);
	return (node);
}

static void	add_envp_list(char *str_envp, t_envp **env)
{
	t_envp	*new;
	t_envp	*last;

	new = new_env_node(str_envp);
	if (!*env)
	{
		*env = new;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_envp	*init_env(char *envp[])
{
	t_envp	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		add_envp_list(envp[i], &env_list);
		i++;
	}
	return (env_list);
}

char	*get_env_value(t_envp *list, char *key)
{
	while (list)
	{
		if (!ft_strcmp(list->key, key))
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

void	set_env_value(t_envp **env_list, char *key, char *new_value)
{
	t_envp	*current;
	char	*aux;
	char	*tmp;

	current = *env_list;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			return ;
		}
		current = current->next;
	}

	tmp = ft_strjoin(key, "=");
	aux = ft_strjoin(tmp, new_value);
	free(tmp);
	add_envp_list(aux, env_list);
	free(aux);
}
