/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 16:27:06 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:40:10 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Fills a memory block with zeroes
 * @param ptr A pointer to the memory block to be filled
 * @param n Amount of bytes to fill
 */
void	ft_bzero(void *ptr, size_t n)
{
	ft_memset(ptr, '\0', n);
}
