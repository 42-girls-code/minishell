/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:52:25 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:13:48 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
int	main(void)
{
	int	v1 = 'C';
	int	v2 = 'c';
	int	v3 = 'I';
	int	v4 = '9';
	printf("%c\n", ft_tolower(v1));
	printf("%c\n", ft_tolower(v2));
	printf("%c\n", ft_tolower(v3));
	printf("%c\n", ft_tolower(v4));
}*/
