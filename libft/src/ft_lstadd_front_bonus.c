/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:41:55 by ingrid            #+#    #+#             */
/*   Updated: 2025/11/12 13:10:58 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*head = NULL;

	int	a = 10;
	int	b = 20;
	int	c = 30;

	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	t_list	*node3 = malloc(sizeof(t_list));

	node1->content = &a;
	node1->next = NULL;

	node2->content = &b;
	node2->next = NULL;

	node3->content = &c;
	node3->next = NULL;

	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);

	t_list *current = head;
	while (current != NULL)
	{
		printf("Nó: %p, Conteúdo: %d, Endereço do conteúdo: %p, Próximo: %p\n",
		(void *)current,
		*(int *)(current->content),
		current->content,
		(void *)current->next);
		current = current->next;
	}
	return (0);
}*/
