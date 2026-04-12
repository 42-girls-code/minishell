/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:15:57 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/09 11:46:20 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int		init_pipe(int fd[2]);
static pid_t	fork_left(t_ast *node, t_minishell *shell, int fd[2]);
static pid_t	fork_right(t_ast *node, t_minishell *shell, int fd[2]);
static void		close_fd_and_wait(int fd[2], pid_t pid[2], t_minishell *shell);

int	exec_pipe(t_ast *node, t_minishell *shell)
{
	int		fd[2];
	pid_t	pid[2];

	if (init_pipe(fd))
		return (1);
	pid[0] = fork_left(node, shell, fd);
	if (pid[0] < 0)
	{
		perror("fork");
		return (1);
	}
	pid[1] = fork_right(node, shell, fd);
	if (pid[1] < 0)
	{
		perror("fork");
		return (1);
	}
	close_fd_and_wait(fd, pid, shell);
	return (0);
}

static int	init_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static pid_t	fork_left(t_ast *node, t_minishell *shell, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd[1]);
		exit(execute_ast(node->left, shell));
	}
	return (pid);
}

static pid_t	fork_right(t_ast *node, t_minishell *shell, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd[0]);
		exit(execute_ast(node->right, shell));
	}
	return (pid);
}

static void	close_fd_and_wait(int fd[2], pid_t pid[2], t_minishell *shell)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], &status, 0);
	waitpid(pid[0], NULL, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
}
