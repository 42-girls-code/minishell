/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:10:22 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/09 20:10:40 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
