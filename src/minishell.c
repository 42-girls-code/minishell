/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:19:24 by ingrid            #+#    #+#             */
/*   Updated: 2026/02/26 00:59:36 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*input = "cat ||| <>>>";
	int		i;

	ft_printf("Bem Vindo ao MiniShell\n");
	tokens = lexer(input);
	tmp = tokens;
	if (!tmp)
	{
		printf("Lexer error\n");
		return (1);
	}
	i = 0;
	while (tmp)
	{
		printf("[TOKEN-%d] type: %d value: %s\n", i, tmp->type, tmp->value);
		i++;
		tmp = tmp->next;
	}
	free_tokens(tokens);
	return (0);
}


// static void	print_tokens(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("TYPE: %d | VALUE: [%s]\n",
// 			tokens->type,
// 			tokens->value ? tokens->value : "NULL");
// 		tokens = tokens->next;
// 	}
// }

// input = "echo 'cat' \"dog\" a''b";
// input = "''";
// input = "a\"\"b";
// input = "'abc";
// input = "\"abc";
// input = "ls | grep cat";
// input = "ls|grep cat"
// input = "cat<<EOF"
