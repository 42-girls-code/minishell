/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:08 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/26 16:31:39 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	setup_redirection(t_ast *cmd);
static void	handle_child(t_ast *cmd, t_envp *env_list);

int	exec_command(t_ast *cmd, t_envp *env_list)
{
	pid_t	pid;

	if (is_builtin(cmd->args[0]))
		return (exec_builtin(cmd, env_list));
	pid = fork();
	if (pid == 0)
	{
		setup_redirection(cmd);
		handle_child(cmd, env_list);
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
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static void	handle_child(t_ast *cmd, t_envp *env_list)
{
	char	*path;
	char	**envp_exec;

	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, env_list));
	path = get_cmd_path(cmd->args[0]);
	if (!path)
		exit(127);
	envp_exec = env_list_to_array(env_list);
	execve(path, cmd->args, envp_exec);
	free(path);
	ft_free_array(envp_exec);
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
