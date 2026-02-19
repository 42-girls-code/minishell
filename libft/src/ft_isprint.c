/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:29:52 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:09:18 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	v_1 = ' ';
	int v_2 = '\t';
	int v_3 = '0';
	int v_4 = 'a';
	int v_5 = 9;

	printf("%d\n", ft_isprint(v_1));
	printf("%d\n", ft_isprint(v_2));
	printf("%d\n", ft_isprint(v_3));
	printf("%d\n", ft_isprint(v_4));
	printf("%d\n", ft_isprint(v_5));

	return (0);
}*/
