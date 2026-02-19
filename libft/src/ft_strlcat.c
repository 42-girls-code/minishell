/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:03:17 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:13:13 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_length;
	size_t	src_length;

	i = 0;
	dst_length = 0;
	src_length = 0;
	while (dst[dst_length] && dst_length < size)
		dst_length++;
	while (src[src_length])
		src_length++;
	if (dst_length == size)
		return (size + src_length);
	while (src[i] && (dst_length + i + 1 < size))
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + src_length);
}
/*
int main(void)
{
	char dst[100] = "Hello 4";
	const char *src = "2 World";
	size_t size = 15;
	size_t  ret = ft_strlcat(dst, src, size);
	printf("dst: %s\n", dst);
	printf("Return: %ld\n", ret);
	return (0);
}*/
