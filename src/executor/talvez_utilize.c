/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talvez_utilize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:07:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/07 17:13:43 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**env_list_to_arr(t_envp *env_list)
{
	char	**array;
	t_envp	*tmp;
	int		i;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	array = malloc(sizeof(char*) * (i + 1));
	if (!array)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		array[i] = ft_strjoin(tmp->key, "=");
		array[i] = ft_strjoin(array[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

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
