/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:10:18 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/26 16:59:54 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include "parser.h"
# include "built_in.h"

//execute.c
int		execute_ast(t_ast *node, t_envp *env_list);

//execute_cmd
int		exec_command(t_ast *cmd, t_envp *env_list);
int		exec_builtin(t_ast *cmd, t_envp *env_list);

//execute_utils.c
char	*get_cmd_path(char *cmd);
char	*double_join(char *s1, char *s2, char *s3);
void	ft_free_array(char **array);

// execute_pipe
int		exec_pipe(t_ast *node, t_envp *env_list);

#endif
