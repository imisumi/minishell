/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:42:38 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 18:00:10 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Calculates the length of a string
 * @param ptr The string to measure
 * @returns The number characters in the string
 */
size_t	ft_strlen(const char *ptr)
{
	size_t	counter;

	counter = 0;
	while (ptr[counter] != '\0')
		counter++;
	return (counter);
}
