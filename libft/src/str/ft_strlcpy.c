/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:01:12 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:57:56 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Copies a string to a different string
 * @param dst A pointer to the destination
 * @param src The string to copy
 * @param dstsize The number of characters available in dst (including the '\0')
 * @returns The number of characters not copied
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		index;

	index = 0;
	if (dstsize != 0)
	{
		while (index + 1 < dstsize && src[index] != '\0')
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	while (src[index] != '\0')
		index++;
	return (index);
}
