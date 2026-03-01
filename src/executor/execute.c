/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:12:41 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/01 12:22:22 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	env_init(char *envp[])
{
	
}

// char	*ft_getenv(char *envp[])
// {
// 	int		i;
// 	char	*path_key;

// 	i = 0;
// 	path_key = "PATH=";
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], path_key, ft_strlen(path_key)))
// 			return (envp[i] + ft_strlen(path_key));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	execute_cmd(char *cmd_str, char *envp[])
// {
// 	char	**cmd_array;
// 	char	*full_path;

// 	cmd_array = ft_split(cmd_str, ' ');
// 	if (!cmd_array)
// 		exit(1);
// 	full_path = get_cmd_path(cmd_array[0], envp);
// 	if (!full_path)
// 	{
// 		ft_printf("%s: %s\n", cmd_array[0], strerror(errno));
// 		ft_free_array(cmd_array);
// 		exit(127);
// 	}
// 	execve(full_path, cmd_array, envp);
// 	perror("Execve failed\n");
// 	free(full_path);
// 	ft_free_array(cmd_array);
// 	exit(1);
// }

// void	ft_free_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	if (!array)
// 		return ;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// char	*get_cmd_path(char *cmd, char *envp[])
// {
// 	char	**paths_array;
// 	char	*path_result;
// 	char	*paths_str;
// 	int		i;

// 	paths_str = ft_getenv(envp);
// 	if (!paths_str)
// 		return (NULL);
// 	paths_array = ft_split(paths_str, ':');
// 	if (!paths_array)
// 		return (NULL);
// 	i = 0;
// 	while (paths_array[i])
// 	{
// 		path_result = join_path_cmd(paths_array[i], cmd);
// 		if (access(path_result, X_OK) == 0)
// 		{
// 			ft_free_array(paths_array);
// 			return (path_result);
// 		}
// 		free(path_result);
// 		i++;
// 	}
// 	ft_free_array(paths_array);
// 	return (NULL);
// }

// char	*join_path_cmd(char *path, char *cmd)
// {
// 	char	*aux;
// 	char	*path_cmd;

// 	aux = ft_strjoin(path, "/");
// 	if (!aux)
// 		return (NULL);
// 	path_cmd = ft_strjoin(aux, cmd);
// 	free(aux);
// 	return (path_cmd);
// }
