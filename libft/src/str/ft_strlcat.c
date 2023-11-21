/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:00:19 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:59:01 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Appends a string to a different string
 * @param dst The string to be appended to
 * @param src The string to append
 * @param dstsize The number of characters available in dst (including the '\0')
 * @returns The number of characters not copied
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len;

	len = 0;
	while (len != dstsize && dst[len] != '\0')
		len++;
	return (ft_strlcpy(&dst[len], src, dstsize - len) + len);
}
