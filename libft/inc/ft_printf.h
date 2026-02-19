/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:27:20 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:10:04 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_direction(char c, va_list args);

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr_len(int n);
void	ft_putnbr(int n);

int		ft_putnbr_len_unsigned(unsigned int n);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_hex_len(unsigned int n, char c);

int		ft_putptr_len(void *ptr);
void	ft_putptr_hex(void *ptr);
void	ft_puthex_ulong(unsigned long n);

#endif
