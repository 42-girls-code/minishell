/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:27 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:10:51 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	get_length(long n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*allocate_string(int len, int is_negative)
{
	char	*n;

	n = malloc (sizeof(char) * (len + is_negative + 1));
	if (!n)
		return (NULL);
	return (n);
}

static void	fill_digits(char *str, long n, int index)
{
	if (n == 0)
	{
		str[index] = '0';
		return ;
	}
	while (n > 0)
	{
		str[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		is_negative;
	long	nbr;
	int		len;

	is_negative = 0;
	nbr = (long)n;
	if (n < 0)
	{
		is_negative = 1;
		nbr = -nbr;
	}
	len = get_length(nbr);
	ptr = allocate_string(len, is_negative);
	if (!ptr)
		return (NULL);
	fill_digits(ptr, nbr, len + is_negative - 1);
	if (is_negative)
		ptr[0] = '-';
	ptr[len + is_negative] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	int	n = -42;
	char	*ptr = ft_itoa(n);
	printf("%s\n", ptr);
	free (ptr);
	return (0);
}*/
