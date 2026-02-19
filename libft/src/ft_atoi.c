/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:04:06 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:08:41 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
int main()
{
	char *ex1 = "  123";
    char *ex2 = "-456";
    char *ex3 = "+789";
    char *ex4 = "42abc";
    char *ex5 = "abc42";

    printf("\"%s\" -> %d\n", ex1, ft_atoi(ex1));
    printf("\"%s\" -> %d\n", ex2, ft_atoi(ex2));
    printf("\"%s\" -> %d\n", ex3, ft_atoi(ex3));
    printf("\"%s\" -> %d\n", ex4, ft_atoi(ex4));
    printf("\"%s\" -> %d\n", ex5, ft_atoi(ex5));
	return 0;
}*/
