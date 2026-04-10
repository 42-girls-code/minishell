/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:46:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/10 15:41:05 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <readline/readline.h>
#include "signal.h"

static int	handle_heredoc(t_ast *cmd, t_minishell *shell);
static int	read_heredoc(int write_fd, char *delimiter, t_minishell *shell);
static void	handle_sigint_heredoc(int sig);
static void	setup_heredoc_signals(void);

int	prepare_heredocs(t_ast *node, t_minishell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
	{
		if (handle_heredoc(node, shell))
			return (1);
	}
	if (prepare_heredocs(node->left, shell))
		return (1);
	if (prepare_heredocs(node->right, shell))
		return (1);
	return (0);
}

static int	handle_heredoc(t_ast *cmd, t_minishell *shell)
{
	int	fd[2];

	if (!cmd->heredoc_delim)
		return (0);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	if (read_heredoc(fd[1], cmd->heredoc_delim, shell))
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	close(fd[1]);
	cmd->heredoc_fd = fd[0];
	return (0);
}

static int	read_heredoc(int write_fd, char *delimiter, t_minishell *shell)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			shell->last_status = 130;
			if (line)
				free(line);
			setup_signals();
			return (1);
		}
		if (!line)
		{
			setup_signals();
			return (0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	setup_signals();
	return (0);
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_done = 1;
}

static void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
