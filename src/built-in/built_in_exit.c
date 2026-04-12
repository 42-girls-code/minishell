/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:42:26 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/12 14:58:24 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	is_numeric(char *str);

int	builtin_exit(char **args, t_minishell *shell)
{
	int	code;

	ft_putstr_fd("exit\n", 1);
	if (!args[1])
	{
		code = shell->last_status;
		free_env_list(shell->env);
		exit(code);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		free_env_list(shell->env);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	code = ft_atoi(args[1]) % 256;
	free_env_list(shell->env);
	exit(code);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
