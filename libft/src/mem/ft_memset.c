/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 13:34:08 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:39:41 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Fills a memory block with a value
 * @param ptr A pointer to the memory block to be filled
 * @param c The byte-value to fill with
 * @param n Amount of bytes to fill
 */
void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned long	counter;
	unsigned char	*str;

	str = ptr;
	counter = 0;
	while (counter != n)
	{
		str[counter] = c;
		counter++;
	}
	return (str);
}
