/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:51:04 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/09 22:13:56 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_builtin(char *cmd)
{
	char	**array_built_in;
	int		i;

	array_built_in = arr_builtin();
	i = 0;
	while (array_built_in[i])
	{
		if (!ft_strcmp(cmd, array_built_in[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**arr_builtin(void)
{
	static char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}
