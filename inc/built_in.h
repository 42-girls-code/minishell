/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:28:53 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/09 12:54:59 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

//built_in.c
int		builtin_echo(char **args, t_envp *env_list);

//built_in_utils.c
int		is_builtin(char *cmd);
char	**arr_builtin(void);

#endif
