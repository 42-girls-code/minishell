/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:14:53 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:11:36 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*v_dest;
	const unsigned char	*v_src;

	i = 0;
	v_dest = (unsigned char *)dest;
	v_src = (const unsigned char *)src;
	if ((dest == NULL && src == NULL) || n == 0)
		return (dest);
	if (v_dest < v_src)
	{
		while (i++ < n)
		{
			v_dest[i - 1] = v_src[i - 1];
		}
	}
	else
	{
		while (n-- > 0)
		{
			v_dest[n] = v_src[n];
		}
	}
	return (dest);
}
/*
int	main(void)
{
	printf("Test 1\n");
	char dest_2[10];
	char src_2[] = "abcdef";
	printf("Antes:  %s\n", src_2);
	ft_memmove(dest_2, src_2, 6);
	printf("Depois: %s\n", src_2);

	printf("Test 2\n");
	char buffer[] = "1234567890";
	printf("Antes:  %s\n", buffer);
	ft_memmove(buffer + 2, buffer, 5);
	printf("Depois: %s\n", buffer);

	printf("Test 3\n");
	char buffer_2[] = "1234567890";
	printf("Antes:  %s\n", buffer_2);
	ft_memmove(buffer_2, buffer_2 + 2, 5);
	printf("Depois: %s\n", buffer_2);
	return (0);
}*/
