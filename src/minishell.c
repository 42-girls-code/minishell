/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:19:24 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/10 17:19:10 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// int	main(void)
// {
// 	char	*line;

// 	setup_signals();
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break ;
// 		if (!is_empty(line))
// 		{
// 			add_history(line);
// 			handle_input(line);
// 		}
// 		free(line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }

static void	init_t_minishell(t_minishell *shell, char *envp[])
{
	shell->last_status = 0;
	shell->env = init_env(envp);
}
 
int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_minishell	shell;
 
	(void)argc;
	(void)argv;
	init_t_minishell(&shell, envp);
	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
			continue ;
		}
		if (!is_empty(line))
		{
			add_history(line);
			handle_input(line, &shell);
		}
		if (g_signal == SIGINT)
			g_signal = 0;
		free(line);
	}
	rl_clear_history();
	free_env_list(shell.env);
	return (0);
}
 