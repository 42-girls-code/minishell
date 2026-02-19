/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:03:32 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:13:36 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char *s = "Ingrid";
	int c = 'm';

	size_t	j;
	char *ptr = ft_strrchr(s, c);
	if (ptr != NULL)
		printf("Caracter encontrado: %s.", ptr);
	else
		printf("Caracter não encontrado");
	return (0);
}*/
