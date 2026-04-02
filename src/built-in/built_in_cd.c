/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:29 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/01 21:44:42 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	check_args_count(char **args);
static int	handle_cd_cases(char *arg, t_minishell *shell);
static int	cd_oldpwd(t_minishell *shell, char *path);
static void	update_pwd_env(t_minishell *shell, char *old, char *pwd);

int	builtin_cd(char **args, t_minishell *shell)
{
	char	pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX) || check_args_count(args))
		return (1);
	if (handle_cd_cases(args[1], shell))
		return (1);
	if (!getcwd(pwd, PATH_MAX))
		return (1);
	update_pwd_env(shell, old_pwd, pwd);
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

static int	handle_cd_cases(char *arg, t_minishell *shell)
{
	char	*path;

	if (!arg || (arg[0] == '~' && !arg[1]))
	{
		path = get_env_value(shell->env, "HOME");
		if (!path || chdir(path) == -1)
			return (1);
	}
	else if (arg[0] == '-' && !arg[1])
		return (cd_oldpwd(shell, NULL));
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

static int	cd_oldpwd(t_minishell *shell, char *path)
{
	path = get_env_value(shell->env, "OLDPWD");
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

static void	update_pwd_env(t_minishell *shell, char *old, char *pwd)
{
	set_env_value(&shell->env, "OLDPWD", old);
	set_env_value(&shell->env, "PWD", pwd);
}
