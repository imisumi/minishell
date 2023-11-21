/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 16:57:25 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:36:25 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Copies a memory block to another, non-overlapping, memory block
 * @param pdst The memory block to copy to
 * @param psrc The memory block to copy from
 * @param n The number of bytes to copy
 * @returns A pointer to the destination
 */
void	*ft_memcpy(void *pdst, const void *psrc, size_t n)
{
	size_t		index;
	char		*dst;
	const char	*src;

	index = 0;
	dst = pdst;
	src = psrc;
	if (dst != NULL || src != NULL)
	{
		while (index != n)
		{
			dst[index] = src[index];
			index++;
		}
	}
	return (dst);
}
