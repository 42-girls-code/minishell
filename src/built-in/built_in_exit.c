/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:42:26 by cris_sky          #+#    #+#             */
/*   Updated: 2026/04/13 19:15:05 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	is_numeric(char *str);
static int	set_exit_status(t_minishell *shell, int code);

int	builtin_exit(char **args, t_minishell *shell)
{
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		return (set_exit_status(shell, shell->last_status));
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (set_exit_status(shell, 2));
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (set_exit_status(shell, ft_atoi(args[1]) % 256));
}

static int	set_exit_status(t_minishell *shell, int code)
{
	shell->should_exit = 1;
	shell->last_status = code;
	return (code);
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
