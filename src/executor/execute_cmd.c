/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:08 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/09 22:12:38 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	setup_redirection(t_ast *cmd, int fd[2])
{
	int	flags;

	fd[0] = 0;
	fd[1] = 1;
	if (cmd->infile)
		fd[0] = open(cmd->infile, O_RDONLY);
	if (cmd->outfile)
	{
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		if (cmd->append)
			flags = O_CREAT | O_WRONLY | O_APPEND;
		fd[1] = open(cmd->outfile, flags, 0644);
	}
	return (0);
}

static void	handle_child(t_ast *cmd, t_envp **env_list, char *envp[], int fd[2])
{
	char	*path;

	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, env_list));
	path = get_cmd_path(cmd->args[0], envp);
	if (!path)
		exit(127);
	execve(path, cmd->args, envp);
	free(path);
	exit(127);
}

static void	cleanup_fds(int fd[2])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

int	exec_command(t_ast *cmd, t_envp **env_list, char *envp[])
{
	int		fd[2];
	int		pid;
	int		status;

	setup_redirection(cmd, fd);
	pid = fork();
	if (pid == 0)
		handle_child(cmd, env_list, envp, fd);
	waitpid(pid, &status, 0);
	cleanup_fds(fd);
	return (WEXITSTATUS(status));
}

int	exec_builtin(t_ast *cmd, t_envp **env_list)
{
	char	*t_cmd;

	t_cmd = cmd->args[0];
	if (!ft_strcmp(t_cmd, "echo"))
		return (builtin_echo(cmd->args, *env_list));
	if (!ft_strcmp(t_cmd, "cd"))
		return (builtin_cd(cmd->args, env_list)); // estou aqui!!!
}
