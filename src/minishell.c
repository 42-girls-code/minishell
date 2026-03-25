/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:19:24 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/25 11:50:48 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// int	main(void)
// {
// 	char	*line;

// 	setup_signals();
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			break ;
// 		if (!is_empty(line))
// 		{
// 			add_history(line);
// 			handle_input(line);
// 		}
// 		free(line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (!is_empty(line))
		{
			add_history(line);
			handle_input(line, envp);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
