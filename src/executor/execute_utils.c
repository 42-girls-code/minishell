/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:45 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/26 16:59:14 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_free_array(char **array)
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

char	*double_join(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

char	*get_cmd_path(char *cmd)
{
	char	**paths_array;
	char	*path_result;
	char	*paths_str;
	int		i;

	paths_str = getenv("PATH");
	if (!paths_str)
		return (NULL);
	paths_array = ft_split(paths_str, ':');
	if (!paths_array)
		return (NULL);
	i = 0;
	while (paths_array[i])
	{
		path_result = double_join(paths_array[i], "/", cmd);
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
