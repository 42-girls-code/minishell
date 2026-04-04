/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:28:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/04 10:22:53 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

# define PATH_MAX 1024

//built_in.c
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_env(t_envp *env_list);

int		builtin_cd(char **args, t_minishell *shell);

//built_in_utils.c
int		is_builtin(char *cmd);
char	**arr_builtin(void);
int		is_parent_builtin(char *cmd);

#endif
