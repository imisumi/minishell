/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:18:50 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:32:55 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

/**
 * Compares two memory blocks
 * @param str1 The first memory block
 * @param str2 The second memory block
 * @param n The number of bytes to compare
 * @returns The difference between the first divergent bytes (str1 - str2),
 * 0 if all n bytes are the same
 */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}
