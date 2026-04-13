/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:46:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/12 20:58:53 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <signal.h>

static int	read_heredoc(int write_fd, char *delim, t_minishell *shell);
static int	handle_redir_heredoc(t_redir *r, t_ast *cmd,
				t_minishell *shell);

int	prepare_heredocs(t_ast *node, t_minishell *shell)
{
	t_redir	*r;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
	{
		r = node->redirs;
		while (r)
		{
			if (r->type == TOKEN_HEREDOC)
				if (handle_redir_heredoc(r, node, shell))
					return (1);
			r = r->next;
		}
	}
	if (prepare_heredocs(node->left, shell))
		return (1);
	return (prepare_heredocs(node->right, shell));
}

static int	handle_redir_heredoc(t_redir *r, t_ast *cmd,
	t_minishell *shell)
{
	int	fd[2];

	(void)r;
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	if (read_heredoc(fd[1], r->file, shell))
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	close(fd[1]);
	cmd->heredoc_fd = fd[0];
	return (0);
}

static int	read_heredoc(int write_fd, char *delim, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		run_heredoc_child(write_fd, delim, shell);
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
