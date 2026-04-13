/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:10:59 by csuomins          #+#    #+#             */
/*   Updated: 2026/04/13 19:11:38 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
