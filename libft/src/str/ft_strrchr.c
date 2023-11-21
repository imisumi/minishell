/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 12:27:32 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 18:05:39 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

/**
 * Searches for the last occurence of a character in a string
 * @param s The string to search in
 * @param c The character to search for
 * @returns A pointer to the last occurence of the character, NULL if not found
 */
char	*ft_strrchr(const char *s, int c)
{
	char		*temp;
	char		*str;
	int			i;

	temp = NULL;
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			temp = &str[i];
		i++;
	}
	if (c == '\0')
		temp = &str[i];
	return (temp);
}
