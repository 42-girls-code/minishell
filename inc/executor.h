/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:10:18 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/15 17:12:40 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>

typedef struct s_envp	t_envp;
typedef struct s_ast	t_ast;

//execute.c
int		execute_ast(t_ast *node, t_envp *env_list, char *envp[]);

//execute_cmd
int		exec_command(t_ast *cmd, t_envp *env_list, char *envp[]);
int		exec_builtin(t_ast *cmd, t_envp *env_list);

//execute_utils.c
char	*get_cmd_path(char *cmd);
void	close_fd_and_wait(int fd[2], pid_t pid[2]);

// execute_pipe
int		exec_pipe(t_ast *node, t_envp *env_list, char *env[]);

#endif
