/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:24:12 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:09:10 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int v_1 = 'a';
	int v_2 = 9;
	int v_3 = '0';
	int v_4 = '\n';
	int v_5 = '\t';

	printf("%d\n", ft_isascii(v_1));
	printf("%d\n", ft_isascii(v_2));
	printf("%d\n", ft_isascii(v_3));
	printf("%d\n", ft_isascii(v_4));
	printf("%d\n", ft_isascii(v_5));
	return(0);
}*/
