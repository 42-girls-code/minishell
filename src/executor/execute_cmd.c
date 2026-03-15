/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:08 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/15 16:51:57 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

static void	setup_redirection(t_ast *cmd);
static void	handle_child(t_ast *cmd, t_envp *env_list, char *envp[]);

int	exec_command(t_ast *cmd, t_envp *env_list, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_redirection(cmd);
		handle_child(cmd, env_list, envp);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

static void	setup_redirection(t_ast *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND | 0644);
		else
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC | 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static void	handle_child(t_ast *cmd, t_envp *env_list, char *envp[])
{
	char	*path;

	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, env_list));
	path = get_cmd_path(cmd->args[0]);
	if (!path)
		exit(127);
	execve(path, cmd->args, envp);
	free(path);
	exit(127);
}

int	exec_builtin(t_ast *cmd, t_envp *env_list)
{
	char	*t_cmd;

	t_cmd = cmd->args[0];
	if (!ft_strcmp(t_cmd, "echo"))
		return (builtin_echo(cmd->args, env_list));
	if (!ft_strcmp(t_cmd, "cd"))
		return (builtin_cd(cmd->args, &env_list));
	if (!ft_strcmp(t_cmd, "pwd"))
		return (builtin_pwd());
	//if (!ft_strcmp(t_cmd, "export"))// estou aqui!!!
	return (0);
}
