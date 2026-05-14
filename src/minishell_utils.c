/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:10:22 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/13 19:05:00 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <readline/readline.h>

static int	fill_env_array(char **envp_exec, t_envp *env_list);

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

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**env_list_to_array(t_envp *env_list, t_envp *tmp)
{
	char	**envp_exec;
	int		size;

	tmp = env_list;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	envp_exec = malloc(sizeof(char *) * (size + 1));
	if (!envp_exec)
		return (NULL);
	if (!fill_env_array(envp_exec, env_list))
	{
		free(envp_exec);
		return (NULL);
	}
	return (envp_exec);
}

static int	fill_env_array(char **envp_exec, t_envp *env_list)
{
	int		i;
	t_envp	*tmp;

	tmp = env_list;
	i = 0;
	while (tmp)
	{
		envp_exec[i] = double_join(tmp->key, "=", tmp->value);
		if (!envp_exec[i])
		{
			while (--i >= 0)
				free(envp_exec[i]);
			return (0);
		}
		tmp = tmp->next;
		i++;
	}
	envp_exec[i] = NULL;
	return (1);
}

void	init_t_minishell(t_minishell *shell, char *envp[])
{
	shell->last_status = 0;
	shell->should_exit = 0;
	shell->env = init_env(envp);
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
}
