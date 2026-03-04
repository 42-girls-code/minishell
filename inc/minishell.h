/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:57:28 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/04 13:39:08 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "executor.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_minishell
{
	t_envp	*env_list;
	int		last_status;
}	t_minishell;

t_envp	*init_env(char *envp[]);
char	*get_env_value(t_envp *list, char *key);
void	free_env_list(t_envp *list);

#endif
