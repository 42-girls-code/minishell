/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:54:56 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:08:54 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char	buffer[6] = "Ingrid";
	size_t	i = 0;

	ft_bzero(buffer, sizeof(buffer));
	while (i < sizeof(buffer))
	{
		printf("%d", buffer[i]);
		i++;
	}
	return (0);
}*/
