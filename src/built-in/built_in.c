/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:30:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/13 11:48:48 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	builtin_echo(char **args, t_envp *env_list)
{
	int		i;
	int		no_newline;
	char	*value;

	i = 1;
	no_newline = 0;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] == '$')
			value = get_env_value(env_list, args[i] + 1);
		else
			value = args[i];
		write(1, value, ft_strlen(value));
		if (args[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		ft_putstr_fd("pwd: getcwd impossible\n", 2);
		return (1);
	}
	ft_putstr_fd(pwd , 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
