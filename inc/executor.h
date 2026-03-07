/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:10:18 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/07 18:36:28 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//execute_cmd
char	*get_cmd_path(char *cmd, t_envp *env_list);

int		exec_command(t_ast *cmd, t_envp *env_list, char *envp[]);

#endif
