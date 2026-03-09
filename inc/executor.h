/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:10:18 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/09 12:58:07 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//execute.c
int		execute_ast(t_ast *node, t_envp *env_list, char *envp[]);
int		exec_builtin(t_ast *cmd, t_envp *env_list);

//execute_cmd
int		exec_command(t_ast *cmd, t_envp *env_list, char *envp[]);

//execute_utils.c
char	*get_cmd_path(char *cmd, char *envp[]);

#endif
