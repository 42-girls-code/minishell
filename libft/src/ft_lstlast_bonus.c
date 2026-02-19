/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:35:51 by ingrid            #+#    #+#             */
/*   Updated: 2025/11/12 13:11:10 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
/*
int	main (void)
{
	t_list *head = NULL;

	ft_lstadd_front(&head, ft_lstnew("A"));
	ft_lstadd_front(&head, ft_lstnew("B"));
	ft_lstadd_front(&head, ft_lstnew("C"));

	t_list *temp = head;

	while (temp)
	{
		printf("[%s] -> ", (char *)temp->content);
		temp = temp->next;
	}
	printf("NULL\n");

	t_list	*last = ft_lstlast(head);

	if(last)
		printf("Último nó: [%s]\n", (char *)last->content);
	else
		printf("A Lista está vazia\n");

	return (0);
}*/
