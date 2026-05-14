/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csuomins <csuomins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:57:28 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/13 19:01:23 by csuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_minishell
{
	int				last_status;
	int				should_exit;
	t_envp			*env;
	struct s_token	*active_tokens;
	struct s_ast	*active_ast;
}	t_minishell;

//envp.c
t_envp	*init_env(char *envp[]);
char	*get_env_value(t_envp *list, char *key);
void	set_env_value(t_envp **env_list, char *key, char *new_value);

//envp_utils.c
void	free_env_list(t_envp *list);
void	free_split(char **split);
char	**env_list_to_array(t_envp *env_list, t_envp *tmp);
void	init_t_minishell(t_minishell *shell, char *envp[]);
void	cleanup_shell(t_minishell *shell);
void	clean_exit(t_minishell *shell, int status);

extern int	g_signal;

void	setup_signals(void);
void	handle_input(char *line, t_minishell *shell);
int		is_empty(char *line);

#endif
