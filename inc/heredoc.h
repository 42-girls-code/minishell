/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:17:52 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/12 16:01:50 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "parser.h"
# include "minishell.h"

int		prepare_heredocs(t_ast *node, t_minishell *shell);
void	run_heredoc_child(int write_fd, char *delim, t_minishell *shell);
char	*expand_var_heredoc(char *line, t_minishell *shell);
void	setup_heredoc_signals(void);

#endif
