/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:05:54 by ingrid            #+#    #+#             */
/*   Updated: 2025/11/12 13:12:24 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putptr_len(void *ptr)
{
	int				len;
	unsigned long	n_long;

	len = 2;
	ft_putptr_hex(ptr);
	n_long = (unsigned long)ptr;
	if (!ptr)
		return (5);
	while (n_long)
	{
		n_long /= 16;
		len++;
	}
	return (len);
}

void	ft_puthex_ulong(unsigned long n)
{
	char	c;
	int		rest;

	if (n >= 16)
		ft_puthex_ulong(n / 16);
	rest = n % 16;
	if (rest < 10)
		c = rest + '0';
	else
		c = 'a' + (rest - 10);
	write(1, &c, 1);
}

void	ft_putptr_hex(void *ptr)
{
	unsigned long	n;

	n = (unsigned long)ptr;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return ;
	}
	write(1, "0x", 2);
	ft_puthex_ulong(n);
}
