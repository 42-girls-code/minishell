/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:19:24 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 19:37:29 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	args_error(void);

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_minishell	shell;

	if (argc > 1 && argv == NULL)
		return (args_error());
	init_t_minishell(&shell, envp);
	setup_signals();
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
			handle_input(line, &shell);
		}
		free(line);
	}
	cleanup_shell(&shell);
	return (shell.last_status);
}

static int	args_error(void)
{
	ft_putstr_fd("minishell: no args allowed\n", 2);
	return (1);
}
