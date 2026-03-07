/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:08 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/07 17:24:57 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*join_path_cmd(char *path, char *cmd)
{
	char	*aux;
	char	*path_cmd;

	aux = ft_strjoin(path, "/");
	if (!aux)
		return (NULL);
	path_cmd = ft_strjoin(aux, cmd);
	free(aux);
	return (path_cmd);
}

char	*get_cmd_path(char *cmd, t_envp *env_list)
{
	char	**paths_array;
	char	*path_result;
	char	*paths_str;
	int		i;

	paths_str = get_env_value(env_list, "PATH");
	if (!paths_str)
		return (NULL);
	paths_array = ft_split(paths_str, ':');
	if (!paths_array)
		return (NULL);
	i = 0;
	while (paths_array[i])
	{
		path_result = join_path_cmd(paths_array[i], cmd);
		if (access(path_result, X_OK) == 0)
		{
			ft_free_array(paths_array);
			return (path_result);
		}
		free(path_result);
		i++;
	}
	ft_free_array(paths_array);
	return (NULL);
}


