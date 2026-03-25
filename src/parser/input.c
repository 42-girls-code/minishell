/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:56:55 by cris_sky          #+#    #+#             */
/*   Updated: 2026/03/25 12:09:02 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executor.h"

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	handle_input(char *line, char *envp[])
{
	t_token	*tokens;
	t_token	*err_token;
	t_ast	*root;
	t_envp	*env_list;

	tokens = lexer(line);
	if (!tokens)
	{
		ft_putendl_fd(
			"minishell: unexpected EOF while looking for matching quote", 2);
		return ;
	}
	err_token = NULL;
	root = parse(tokens, &err_token);
	if (!root)
	{
		print_parse_error(err_token);
		free_tokens(tokens);
		return ;
	}
	env_list = init_env(envp); //Ingrid - Criei a lista de envp
	execute_ast(root, env_list, envp); //Ingrid - chamei o execute
	free_ast(root);
	free_tokens(tokens);
	free_env_list(env_list); //Ingrid - adicionei
}
