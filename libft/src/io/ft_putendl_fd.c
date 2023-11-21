/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:13:01 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:40:32 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes a string and a newline to a filedescriptor
 * @param s String to write
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	count;

	count = ft_putstr_fd(s, fd);
	if (count < 0)
		return (-1);
	if (ft_putchar_fd('\n', fd) < 0)
		return (-1);
	return (count + 1);
}
