/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:41:06 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/10 13:02:40 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
 
static int	is_valid_identifier(char *str);
static void	print_export_list(t_envp *env);
static int	export_single(char *arg, t_minishell *shell);
 
int	builtin_export(char **args, t_minishell *shell)
{
	int	i;
	int	ret;
 
	if (!args[1])
	{
		print_export_list(shell->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (export_single(args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
 
static int	export_single(char *arg, t_minishell *shell)
{
	char	*key;
	char	*value;
	char	*eq;
 
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!is_valid_identifier(arg))
		{
			ft_putstr_fd("export: not a valid identifier: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		set_env_value(&shell->env, arg, NULL);
		return (0);
	}
	key = ft_substr(arg, 0, eq - arg);
	if (!key || !is_valid_identifier(key))
	{
		ft_putstr_fd("export: not a valid identifier: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("\n", 2);
		free(key);
		return (1);
	}
	value = eq + 1;
	set_env_value(&shell->env, key, value);
	free(key);
	return (0);
}
 
static int	is_valid_identifier(char *str)
{
	int	i;
 
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
 
static void	print_export_list(t_envp *env)
{
	t_envp	*tmp;
 
	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}
