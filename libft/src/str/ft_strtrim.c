/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 15:27:36 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 18:07:29 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Trims a string
 * @param s1 The string to trim
 * @param set A string containing the characters to trim
 * @returns A new trimmed string, NULL on error
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == NULL)
			break ;
		i++;
	}
	if (s1[i] == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s1) - 1;
	while (j != 0)
	{
		if (ft_strchr(set, s1[j]) == NULL)
			break ;
		j--;
	}
	return (ft_substr(s1, i, j - i + 1));
}
