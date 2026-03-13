/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:29 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/13 11:36:39 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	check_args_count(char **args);
static int	handle_cd_cases(char *arg, t_envp **env_list, char *old_pwd);
static int	cd_oldpwd(t_envp **env_list, char *path);
static void	update_pwd_env(t_envp **env_list, char *old, char *pwd);

int	builtin_cd(char **args, t_envp	**env_list)
{
	char	pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX) || check_args_count(args))
		return (1);
	if (handle_cd_cases(args[1], env_list, old_pwd))
		return (1);
	if (!getcwd(pwd, PATH_MAX))
		return (1);
	update_pwd_env(env_list, old_pwd, pwd);
	return (0);
}

static int	check_args_count(char **args)
{
	if (args[2])
	{
		ft_putstr_fd("cd: excessive number if arguments\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_cd_cases(char *arg, t_envp **env_list, char *old_pwd)
{
	char	*path;

	if (!arg || (arg[0] == '~' && !arg[1]))
	{
		path = get_env_value(*env_list, "HOME");
		if (!path || chdir(path) == -1)
			return (1);
	}
	if (arg[0] == '-' && !arg[1])
		return (cd_oldpwd(env_list, path));
	else
	{
		if (chdir(arg) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

static int	cd_oldpwd(t_envp **env_list, char *path)
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
	return (0);
}

static void	update_pwd_env(t_envp **env_list, char *old, char *pwd)
{
	set_env_value(env_list, "OLDPWD", old);
	set_env_value(env_list, "PWD", pwd);
}
