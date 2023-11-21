/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:18:50 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:28:21 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Searches for a character in a memory block
 * @param s The memory block to look through
 * @param c The character to look for
 * @param n The number of bytes to look through in s
 * @returns A pointer to the first occurance of the character,
 * NULL if it hasn't been found
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = s;
	unsigned char		a;
	size_t				i;

	a = c;
	i = 0;
	while (i != n)
	{
		if (str[i] == a)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
