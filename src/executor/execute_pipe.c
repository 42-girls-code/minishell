/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:15:57 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/15 17:10:08 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	exec_pipe(t_ast *node, t_envp *env_list, char *env[])
{
	int		fd[2];
	pid_t	pid[2];

	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_ast(node->left, env_list, env);
		exit(0);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execute_ast(node->right, env_list, env);
		exit(0);
	}
	close_fd_and_wait(fd, pid);
	return (0);
}
