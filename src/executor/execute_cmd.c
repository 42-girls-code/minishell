/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:08 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/09 10:28:11 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	setup_redirection(t_ast *cmd);
static void	handle_child(t_ast *cmd, t_minishell *shell);
static int	exec_with_fork(t_ast *cmd, t_minishell *shell);
static int	exec_without_fork(t_ast *cmd, t_minishell *shell);

int	exec_command(t_ast *cmd, t_minishell *shell)
{
	if (!is_parent_builtin(cmd->args[0]))
		return (exec_with_fork(cmd, shell));
	else
		return (exec_without_fork(cmd, shell));
}

static int	exec_with_fork(t_ast *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (setup_redirection(cmd))
			exit(1);
		if (is_builtin(cmd->args[0]))
			exit(exec_builtin(cmd, shell));
		else
			handle_child(cmd, shell);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	exec_without_fork(t_ast *cmd, t_minishell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;

	if (!is_builtin(cmd->args[0]))
	{
		printf("%s: external control without fork\n", cmd->args[0]);
		return (1);
	}
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
		return (perror("dup"), 1);
	if (setup_redirection(cmd))
		ret = 1;
	else
	{
		ret = exec_builtin(cmd, shell);
		if (dup2(stdin_backup, STDIN_FILENO) < 0
			|| dup2(stdout_backup, STDOUT_FILENO) < 0)
			perror("dup2");
	}
	close(stdin_backup);
	close(stdout_backup);
	return (ret);
}

static int	setup_redirection(t_ast *cmd)
{
	if (cmd->heredoc_fd != -1) //adicionado por causa do heredoc
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (1);
		}
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	else if (cmd->infile)
	{
		if (open_and_dup(cmd->infile, O_RDONLY, STDIN_FILENO))
			return (1);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			return (open_and_dup(cmd->outfile,
					O_CREAT | O_WRONLY | O_APPEND, STDOUT_FILENO));
		else
			return (open_and_dup(cmd->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, STDOUT_FILENO));
	}
	return (0);
}

static void	handle_child(t_ast *cmd, t_minishell *shell)
{
	char	*path;
	char	**envp_exec;
	t_envp	tmp;

	path = get_cmd_path(cmd->args[0]);
	if (!path)
	{
		print_strerror(cmd->args[0]);
		exit(127);
	}
	envp_exec = env_list_to_array(shell->env, &tmp);
	execve(path, cmd->args, envp_exec);
	print_strerror(cmd->args[0]);
	free(path);
	ft_free_array(envp_exec);
	exit(127);
}
