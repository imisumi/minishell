/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 13:50:28 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 18:01:26 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Duplicates a string and transforms its content using f
 * @param s String to be duplicated
 * @param f The function that is called to transform each character,
 * receiving its index and the character itself
 * @returns The new transformed string, NULL on error
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ptr != NULL)
	{
		while (s[i] != '\0')
		{
			ptr[i] = (*f)(i, s[i]);
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
