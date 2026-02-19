/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:12:45 by ingrid            #+#    #+#             */
/*   Updated: 2025/11/12 13:12:54 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_extract_word(char const **s_ptr, char c)
{
	char const	*s;
	char const	*start;
	char		*word;
	size_t		len;

	s = *s_ptr;
	while (*s == c)
		s++;
	start = s;
	while (*s && *s != c)
		s++;
	len = s - start;
	*s_ptr = s;
	word = ft_substr(start, 0, len);
	if (!word)
		return (NULL);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (NULL);
	while (i < word_count)
	{
		words[i] = ft_extract_word(&s, c);
		if (!words[i])
		{
			while (i--)
				free (words[i]);
			free(words);
			return (NULL);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}
/*
int	main(void)
{
	const char	s[100] = " split       this for   me  !       ";
	char		c = ' ';
	char		**words = ft_split(s,c);
	int	i = 0;
	if (!words)
		return (1);
	while (words[i])
	{
		printf("Palavra [%d]: %s\n", i, words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (0);
}*/
