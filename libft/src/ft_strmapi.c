/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:25:16 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:13:24 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_str;

	i = 0;
	if (!s || !f)
		return (NULL);
	new_str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
/*
char	test(unsigned int i, char c)
{
	return (c + i - i);
}

int	main(void)
{
	const char *s = "abcd";
	char	*map = ft_strmapi(s, test);
	if (map)
	{
		printf("%s\n", map);
		free(map);
	}
	return (0);
}*/
