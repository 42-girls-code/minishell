/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:46:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/10 17:41:18 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

static int	handle_heredoc(t_ast *cmd, t_minishell *shell);
static int	read_heredoc(int write_fd, char *delimiter, t_minishell *shell);
static void	run_heredoc_child(int write_fd, char *delimiter);
static void	child_sigint_handler(int sig);

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
		return (perror("pipe"), 1);
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

static void	child_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

static void	run_heredoc_child(int write_fd, char *delimiter)
{
	struct sigaction	sa;
	char				*line;

	sa.sa_handler = child_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd(
				"warning: here-document delimited by end-of-file\n", 2);
			exit(0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			exit(0);
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static int	read_heredoc(int write_fd, char *delimiter, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		setup_signals();
		return (perror("fork"), 1);
	}
	if (pid == 0)
		run_heredoc_child(write_fd, delimiter);
	close(write_fd);
	waitpid(pid, &status, 0);
	g_signal = 0;
	setup_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		shell->last_status = 130;
		return (1);
	}
	return (0);
}
