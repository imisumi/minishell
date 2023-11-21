/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 12:21:25 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:37:09 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Copies a memory block to another, possibly overlapping, memory block,
 * in a non-destructive manner
 * @param pdst The memory block to copy to
 * @param psrc The memory block to copy from
 * @param n The number of bytes to copy
 * @returns A pointer to the destination
 */
void	*ft_memmove(void *pdst, const void *psrc, size_t len)
{
	size_t		index;
	char *const	dst = pdst;
	const char	*src = psrc;

	if (src < dst)
	{
		index = len;
		while (index > 0)
		{
			index--;
			dst[index] = src[index];
		}
	}
	else
	{
		index = 0;
		while (index < len)
		{
			dst[index] = src[index];
			index++;
		}
	}
	return (dst);
}
