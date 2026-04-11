/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 18:35:12 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 19:18:11 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "lexer.h"

typedef enum e_ex_state
{
	DEFAULT,
	S_QUOTE,
	D_QUOTE,
}	t_ex_state;

void	expand_ast(t_ast *root, t_minishell *shell);
char	*expand_var(char *arg, t_minishell *shell);

#endif
