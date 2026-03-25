/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:57:28 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/25 12:09:42 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
// # include "parser.h"
// # include "lexer.h"
// # include "executor.h"
// # include "built_in.h"
# include <sys/wait.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

//envp.c
t_envp	*init_env(char *envp[]);
char	*get_env_value(t_envp *list, char *key);
void	set_env_value(t_envp **env_list, char *key, char *new_value);

//envp_utils.c
void	free_env_list(t_envp *list);

extern int	g_signal;

void	setup_signals(void);
void	handle_input(char *line, char *envp[]); //Ingrid - adicionei o envp
int		is_empty(char *line);

#endif
