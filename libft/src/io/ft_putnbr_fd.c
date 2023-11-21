/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:23:49 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:44:03 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a decimal number to a filedescriptor
 * @param n Number to write
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
ssize_t	ft_putnbr_fd(int n, int fd)
{
	ssize_t	count;

	count = 0;
	if (n < 0)
	{
		if (ft_putchar_fd('-', fd) < 0)
			return (-1);
		if (n < -9)
			count = ft_putnbr_fd(-(n / 10), fd);
		if (count < 0)
			return (-1);
		if (ft_putchar_fd(-(n % 10) + 48, fd) < 0)
			return (-1);
		return (1 + count + 1);
	}
	if (n > 9)
		count = ft_putnbr_fd((n / 10), fd);
	if (count < 0)
		return (-1);
	if (ft_putchar_fd((n % 10) + 48, fd) < 0)
		return (-1);
	return (count + 1);
}
