/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_puthexnbr_fd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 16:35:53 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:44:14 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a hexadecimal number to a filedescriptor
 * @param n Number to write
 * @param uppercase Whether to write in uppercase
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
ssize_t	ft_puthexnbr_fd(unsigned long n, bool uppercase, int fd)
{
	ssize_t					count;
	int						i;
	static const char		low[] = "0123456789abcdef";
	static const char		up[] = "0123456789ABCDEF";

	i = 0;
	count = 0;
	if (n > 15)
		count = ft_puthexnbr_fd((n / 16), uppercase, fd);
	if (count < 0)
		return (-1);
	i = n % 16;
	if (uppercase)
	{
		if (ft_putchar_fd(up[i], fd) < 0)
			return (-1);
	}
	else
	{
		if (ft_putchar_fd(low[i], fd) < 0)
			return (-1);
	}
	return (count + 1);
}

// int	main(void)
// {
// 	ssize_t var = ft_puthnbr_fd(0xf5f1, STDOUT_FILENO);
// 	printf("\nret: %zi\n", var);
// }
