/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:30:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/10 00:13:11 by ingrid           ###   ########.fr       */
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

int	builtin_cd(char **args, t_envp	**env_list)
{
	char	*path;
	char	pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX))
		return (1);
	if (!args[1] || (args[1][0] == '~' && !args[1][1]))
	{
		path = get_env_value(*env_list, "HOME");
		if (!path || chdir(path) == -1)
			return (1);
	}
	else if (args[1][0] == '-' && !args[1][1])
	{
		path = get_env_value(*env_list, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not defined\n", 2);
			return (1);
		}
		if (chdir(path) == -1)
			return (1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	if (!getcwd(pwd, PATH_MAX))
		return (1);
	set_env_value(env_list, "OLDPWD", old_pwd);
	set_env_value(env_list, "PWD", pwd);
	return (0);
}
