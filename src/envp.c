/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 22:04:35 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/04 13:42:00 by ingrid           ###   ########.fr       */
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
	split_result = ft_split(envp,'=');
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
	free(split_result[0]);
	free(split_result[1]);
	free(split_result);
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
		if (ft_strncmp(list->key, key, ft_strlen(key)) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

void	free_env_list(t_envp *list)
{
	t_envp	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free (tmp->key);
		free (tmp->value);
		free(tmp);
	}
}
