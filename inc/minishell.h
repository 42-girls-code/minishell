/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:57:28 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/09 20:10:55 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "executor.h"
# include "built_in.h"

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

//Cris
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	char			*hearedoc_delim;
}	t_ast;
// Fim Cris

t_envp	*init_env(char *envp[]);
char	*get_env_value(t_envp *list, char *key);
void	set_env_value(t_envp **env_list, char *key, char *new_value);

void	free_env_list(t_envp *list);

#endif
