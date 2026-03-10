/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:12:41 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/09 21:03:37 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_ast(t_ast *node, t_envp *env_list, char *envp[])
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (exec_command(node, &env_list, envp));
	if (node->type == NODE_PIPE)
		return (exec_pipe(node->left, node->right, env_list));
	if (node->type == NODE_AND)
		return (exec_and_or(node->left, node->right, 0, env_list));
	if (node->type == NODE_OR)
		return (exec_and_or(node->left, node->right, 1, env_list));
	return (0);
}
