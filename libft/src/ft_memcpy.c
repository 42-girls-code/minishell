/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:05:48 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:11:32 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*v_src;
	char	*v_dest;

	i = 0;
	v_src = (char *)src;
	v_dest = (char *)dest;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		v_dest[i] = v_src[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "Escola 42";
	char	dest[10];

	ft_memcpy(dest, src, sizeof(src));
	printf("%s\n", dest);
	return (0);
}*/
