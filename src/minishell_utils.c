/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:10:22 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 19:39:45 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <readline/readline.h>

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
	int		i;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp_exec = malloc(sizeof(char *) * (i + 1));
	if (!envp_exec)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		envp_exec[i] = double_join(tmp->key, "=", tmp->value);
		if (!envp_exec[i])
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	envp_exec[i] = NULL;
	return (envp_exec);
}

void	init_t_minishell(t_minishell *shell, char *envp[])
{
	shell->last_status = 0;
	shell->env = init_env(envp);
}

void	cleanup_shell(t_minishell *shell)
{
	rl_clear_history();
	free_env_list(shell->env);
}
