/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talvez_utilize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:07:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/08 15:07:19 by ingrid           ###   ########.fr       */
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
