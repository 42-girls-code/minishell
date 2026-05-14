/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:12:41 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/13 14:58:10 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_ast(t_ast *node, t_minishell *shell)
{
	if (!node)
		return (shell->last_status);
	if (node->type == NODE_PIPE)
		return (exec_pipe(node, shell));
	if (node->type == NODE_COMMAND)
		return (exec_command(node, shell));
	// if (node->type == NODE_AND)
	// 	return (exec_and_or(node->left, node->right, 0, env_list));
	// if (node->type == NODE_OR)
	// 	return (exec_and_or(node->left, node->right, 1, env_list));
	return (shell->last_status);
}

int	exec_builtin(t_ast *cmd, t_minishell *shell)
{
	char	*t_cmd;

	t_cmd = cmd->args[0];
	if (!ft_strcmp(t_cmd, "echo"))
		return (builtin_echo(cmd->args));
	if (!ft_strcmp(t_cmd, "cd"))
		return (builtin_cd(cmd->args, shell));
	if (!ft_strcmp(t_cmd, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(t_cmd, "env"))
		return (builtin_env(shell->env));
	if (!ft_strcmp(t_cmd, "export"))
		return (builtin_export(cmd->args, shell));
	if (!ft_strcmp(t_cmd, "unset"))
		return (builtin_unset(cmd->args, shell));
	if (!ft_strcmp(t_cmd, "exit"))
		return (builtin_exit(cmd->args, shell));
	return (0);
}

int	apply_redir(t_redir *r)
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
