/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 15:07:07 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 18:09:17 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * Creates a substring
 * @param s The original string
 * @param start The index where the substring starts
 * @param len The maximum length of the substring
 * @returns The new substring, NULL on error
 */
char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*str;
	char	*ptr;
	size_t	strlen;

	str = (char *)s;
	strlen = ft_strlen(str);
	if (start > strlen)
		return (ft_strdup(""));
	if ((strlen - start) > len)
	{
		ptr = malloc((len + 1) * sizeof(char));
		if (ptr != NULL)
			ft_strlcpy(ptr, &str[start], (len + 1));
	}
	else
	{
		ptr = malloc(((strlen - start) + 1) * sizeof(char));
		if (ptr != NULL)
			ft_strlcpy(ptr, &str[start], ((strlen - start) + 1));
	}
	return (ptr);
}

//rewrite using strnlen as static function,
//comparing start and length as the seperate parts to shorten f.
