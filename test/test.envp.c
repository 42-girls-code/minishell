/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:43:47 by ingrid            #+#    #+#             */
/*   Updated: 2026/03/04 13:44:02 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_envp	*test_list;
	t_envp	*tmp;
	int		i = 0;

	test_list = init_env(envp);
	ft_printf("argc: %d e argv[1]: %s\n", ac, av[1]);
	if (!test_list)
	{
		ft_printf("Erro ao inicializar");
		return (1);
	}
	tmp = test_list;
	while (tmp)
	{
		ft_printf("[%d]: key: %s value: %s\n",i, tmp->key, tmp->value);
		i++;
		tmp = tmp->next;
	}
	char *user = get_env_value(test_list, "USER");
	ft_printf("Resultado da busca por USER: %s\n", user ? user : "Não encontrado");
	free_env_list(test_list);
	return (0);
}
