/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:12:41 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/08 15:10:15 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_ast(t_ast *node, t_envp *env_list, char *envp[])
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (exec_command(node, env_list, envp)); //implementar
	if (node->type == NODE_PIPE)
		return(exec_pipe(node->left, node->right, env_list));
	if (node->type == NODE_AND)
		return (exec_and_or(node->left, node->right, 0, env_list));
	if (node->type == NODE_OR)
		return (exec_and_or(node->left, node->right, 1, env_list));
	return (0);
}
//grupo
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

static void	handle_child(t_ast *cmd, t_envp *env_list, char *envp[], int fd[2])
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

int	exec_command(t_ast *cmd, t_envp *env_list, char *envp[])
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

int	is_builtin(char *cmd)
{
	char	**array_built_in;
	int		i;

	array_built_in = arr_builtin();
	i = 0;
	while (array_built_in[i])
	{
		if (!ft_strncmp(cmd, array_built_in[i], ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}

char	**arr_builtin(void)
{
	static char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}
//FIM GRUPO

int	exec_builtin(t_ast *cmd, t_envp *env_list)
{
	char	*t_cmd;

	t_cmd = cmd->args[0];
	if (!ft_strncmp(t_cmd, "echo", ft_strlen(t_cmd)))
		return (builtin_echo(cmd->args, env_list));
}

int	builtin_echo(char **args, t_envp *env_list)
{
	int		i;
	int		no_newline;
	char	*value;

	i = 1;
	no_newline = 0;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] == '$')
			value = get_env_value(env_list, args[i] + 1);
		else
			value = args[i];
		write(1, value, ft_strlen(value));
		if (args[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}
