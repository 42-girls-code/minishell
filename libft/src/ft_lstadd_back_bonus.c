/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:51:17 by ingrid            #+#    #+#             */
/*   Updated: 2025/11/12 13:10:55 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add_back;

	if (lst)
	{
		if (*lst)
		{
			add_back = *lst;
			while (add_back->next)
				add_back = add_back->next;
			add_back->next = new;
		}
		else
			*lst = new;
	}
}
/*
int	main (void)
{
	t_list *head = NULL;

	ft_lstadd_back(&head, ft_lstnew("A"));
	ft_lstadd_back(&head, ft_lstnew("B"));
	ft_lstadd_back(&head, ft_lstnew("C"));

	t_list *temp = head;

	while (temp)
	{
		printf("[%s] -> ", (char *)temp->content);
		temp = temp->next;
	}
	printf("NULL\n");

	return (0);
}*/
