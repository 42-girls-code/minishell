/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cris_sky <cris_sky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:17:08 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/12 22:11:37 by cris_sky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	setup_redirection(t_ast *cmd);
static void	handle_child(t_ast *cmd, t_minishell *shell);
static int	exec_with_fork(t_ast *cmd, t_minishell *shell);
static int	exec_without_fork(t_ast *cmd, t_minishell *shell);

int	exec_command(t_ast *cmd, t_minishell *shell)
{
	if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (127);
	}
	if (!is_parent_builtin(cmd->args[0]))
		return (exec_with_fork(cmd, shell));
	return (exec_without_fork(cmd, shell));
}

static int	apply_redir(t_redir *r)
{
	if (r->type == TOKEN_REDIR_IN)
		return (open_and_dup(r->file, O_RDONLY, STDIN_FILENO));
	if (r->type == TOKEN_REDIR_OUT)
		return (open_and_dup(r->file,
				O_CREAT | O_WRONLY | O_TRUNC, STDOUT_FILENO));
	if (r->type == TOKEN_APPEND)
		return (open_and_dup(r->file,
				O_CREAT | O_WRONLY | O_APPEND, STDOUT_FILENO));
	return (0);
}

static int	setup_redirection(t_ast *cmd)
{
	t_redir	*r;

	if (cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	r = cmd->redirs;
	while (r)
	{
		if (r->type != TOKEN_HEREDOC && apply_redir(r))
			return (1);
		r = r->next;
	}
	return (0);
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
		handle_child(cmd, shell);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	exec_without_fork(t_ast *cmd, t_minishell *shell)
{
	int	stdin_bk;
	int	stdout_bk;
	int	ret;

	stdin_bk = dup(STDIN_FILENO);
	stdout_bk = dup(STDOUT_FILENO);
	if (stdin_bk < 0 || stdout_bk < 0)
		return (perror("dup"), 1);
	if (setup_redirection(cmd))
		ret = 1;
	else
	{
		ret = exec_builtin(cmd, shell);
		if (dup2(stdin_bk, STDIN_FILENO) < 0
			|| dup2(stdout_bk, STDOUT_FILENO) < 0)
			perror("dup2");
	}
	close(stdin_bk);
	close(stdout_bk);
	return (ret);
}

static void	handle_child(t_ast *cmd, t_minishell *shell)
{
	char	*path;
	char	**envp_exec;
	t_envp	tmp;

	path = get_cmd_path(cmd->args[0], shell);
	if (!path)
	{
    	ft_putstr_fd(cmd->args[0], 2);
    	ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	envp_exec = env_list_to_array(shell->env, &tmp);
	execve(path, cmd->args, envp_exec);
	print_strerror(cmd->args[0]);
	free(path);
	ft_free_array(envp_exec);
	exit(127);
}
