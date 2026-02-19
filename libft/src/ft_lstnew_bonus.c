/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:13:06 by ingrid            #+#    #+#             */
/*   Updated: 2025/11/12 13:11:15 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
/*
int	main(void)
{
	int	a = 10;
	int	b = 20;
	int	c = 30;

	t_list *node1 = ft_lstnew(&a);
	t_list *node2 = ft_lstnew(&b);
	t_list *node3 = ft_lstnew(&c);

	node1->next = node2;
	node2->next = node3;

	t_list *current = node1;
	while (current != NULL)
	{
		printf("%d -> ", *(int *)current->content);
		current = current->next;
	}
	printf("NULL\n");
	t_list *p_current = node1;
	while (p_current != NULL)
	{
		printf("%p -> ", (void *)p_current);
		p_current = p_current->next;
	}
	printf("NULL\n");
	return (0);
}*/
