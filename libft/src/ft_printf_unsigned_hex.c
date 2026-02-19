/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_hex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:32:29 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:12:28 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_putnbr_len_unsigned(unsigned int n)
{
	int	len;

	len = 1;
	ft_putnbr_unsigned(n);
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr_unsigned(n / 10);
		ft_putnbr_unsigned(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
	return (0);
}

static void	ft_hex_lowercase(unsigned int n)
{
	int		rest;
	char	c;

	if (n >= 16)
	{
		ft_hex_lowercase(n / 16);
	}
	rest = n % 16;
	if (rest < 10)
		c = rest + '0';
	else
		c = 'a' + (rest -10);
	write(1, &c, 1);
}

static void	ft_hex_uppercase(unsigned int n)
{
	int		rest;
	char	c;

	if (n >= 16)
	{
		ft_hex_uppercase(n / 16);
	}
	rest = n % 16;
	if (rest < 10)
		c = rest + '0';
	else
		c = 'A' + (rest -10);
	write(1, &c, 1);
}

int	ft_hex_len(unsigned int n, char c)
{
	int	len;

	len = 1;
	if (c == 'x')
		ft_hex_lowercase(n);
	if (c == 'X')
		ft_hex_uppercase(n);
	while (n / 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}
