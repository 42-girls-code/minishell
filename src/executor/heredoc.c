/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilemos-c <ilemos-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:46:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/04/03 15:51:13 by ilemos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	prepare_heredoc(t_ast *node)
{
	char	*line;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, node->heredoc_delim))
			break;

	}
}
