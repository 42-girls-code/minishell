/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:19:24 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/13 19:07:19 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static int	args_error(void);
static void	run_shell_loop(t_minishell *shell);

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	shell;

	if (argc > 1 && argv == NULL)
		return (args_error());
	init_t_minishell(&shell, envp);
	setup_signals();
	run_shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.last_status);
}

static void	run_shell_loop(t_minishell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (g_signal == SIGINT)
			g_signal = 0;
		if (line[0] != '\0' && !is_empty(line))
		{
			add_history(line);
			handle_input(line, shell);
		}
		if (shell->should_exit)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

static int	args_error(void)
{
	ft_putstr_fd("minishell: no args allowed\n", 2);
	return (1);
}

void	clean_exit(t_minishell *shell, int status)
{
	cleanup_shell(shell);
	exit(status);
}

void	cleanup_shell(t_minishell *shell)
{
	if (shell->active_ast)
	{
		free_ast(shell->active_ast);
		shell->active_ast = NULL;
	}
	if (shell->active_tokens)
	{
		free_tokens(shell->active_tokens);
		shell->active_tokens = NULL;
	}
	rl_clear_history();
	free_env_list(shell->env);
	shell->env = NULL;
}
