/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:46:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/12 15:36:56 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <signal.h>

static int	handle_heredoc(t_ast *cmd, t_minishell *shell);
static int	read_heredoc(int write_fd, char *delimiter, t_minishell *shell);

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
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		run_heredoc_child(write_fd, delimiter, shell);
	close(write_fd);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		shell->last_status = 130;
		return (1);
	}
	return (0);
}
