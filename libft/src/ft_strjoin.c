/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:24:39 by ilemos-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:13:09 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new_str;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = "";
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}
/*
int	main(void)
{
	char const *s1 = "42 ";
	char const *s2 = "São Paulo";
	char	*new_str;
	new_str = ft_strjoin(s1, s2);
	if ( new_str == NULL)
		printf("Não foi possível concatenar as strings.\n");
	else{
		printf("%s\n", new_str);
		free(new_str);
	}
	return 0;
}*/
