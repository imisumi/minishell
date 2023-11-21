/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 12:56:06 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:50:03 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * Duplicates a string
 * @param str The string to be duplicated
 * @returns The duplicated string, NULL on error
 */
char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	count;

	count = (ft_strlen(str) + 1);
	ptr = malloc(count * sizeof(char));
	if (ptr != NULL)
		ft_strlcpy(ptr, str, count);
	return (ptr);
}
