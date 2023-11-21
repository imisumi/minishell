/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putunbr_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 13:47:39 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:45:28 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a unsigned decimal number to a filedescriptor
 * @param n Number to write
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
ssize_t	ft_putunbr_fd(unsigned int n, int fd)
{
	ssize_t	count;

	count = 0;
	if (n > 9)
		count = ft_putunbr_fd((n / 10), fd);
	if (count < 0)
		return (-1);
	if (ft_putchar_fd((n % 10) + 48, fd) < 0)
		return (-1);
	return (count + 1);
}
