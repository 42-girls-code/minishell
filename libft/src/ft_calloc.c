/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:26:36 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:08:58 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	if (elsize != 0 && nelem > SIZE_MAX / elsize)
		return (NULL);
	if (nelem == 0 || elsize == 0)
	{
		nelem = 1;
		elsize = 1;
	}
	ptr = malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, (nelem * elsize));
	return (ptr);
}
/*
int	main(void)
{
	int	*arr;
	size_t i = 0;
	size_t j = 10;

	arr = (int *)ft_calloc(j, sizeof(int));
	if (arr == NULL)
		printf("Erro na alocação de memória!\n");
	printf("Valores após alocação e zeragem:\n");
	while (i < j)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	free(arr);
	return (0);
}*/
