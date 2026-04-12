/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:17:52 by ingrid            #+#    #+#             */
/*   Updated: 2026/04/11 20:25:07 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "parser.h"

int		prepare_heredocs(t_ast *node, t_minishell *shell);
char	*expand_var_heredoc(char *line, t_minishell *shell);

#endif
