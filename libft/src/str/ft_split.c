/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 12:27:22 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:49:08 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_nstrchr(const char *s, int c)
{
	char	a;
	int		i;

	a = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != a)
			return ((char *)&s[i]);
		i++;
	}
	if (a == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static unsigned long	ft_get_word_count(char const *s, char c)
{
	unsigned long	i;
	char			*start;
	char			*end;

	end = (char *)s;
	i = 0;
	while (end != NULL && *end != '\0')
	{
		start = ft_nstrchr(end, c);
		if (start == NULL)
			break ;
		end = ft_strchr(start, c);
		i++;
	}
	return (i);
}

static char	**ft_free_split(char **arr)
{
	unsigned long	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**ft_fill_arr(char const *s, char c, char **arr)
{
	unsigned long	i;
	char			*start;
	char			*end;

	end = (char *)s;
	i = 0;
	while (end != NULL && *end != '\0')
	{
		start = ft_nstrchr(end, c);
		if (start == NULL)
			break ;
		end = ft_strchr(start, c);
		if (end == NULL)
			arr[i] = ft_strdup(start);
		else
			arr[i] = ft_substr(s, start - s, (end - start));
		if (arr[i] == NULL)
			return (ft_free_split(arr));
		i++;
	}
	return (arr);
}

/**
 * Splits a string into an array of strings seperated by c
 * @param s The string to split
 * @param c The seperating character
 * @returns An array of strings, NULL on error
 */
char	**ft_split(char const *s, char c)
{
	unsigned long	i;
	char			**arr;

	i = ft_get_word_count(s, c);
	arr = malloc((i + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr[i] = NULL;
	return (ft_fill_arr(s, c, arr));
}
