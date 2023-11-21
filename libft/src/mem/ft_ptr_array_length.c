/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptr_array_length.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 15:57:54 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:41:07 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Calculates the length of a NULL-terminated array
 * @param array The array to be measured
 * @returns The length of the array
 */
size_t	ft_ptr_array_length(void **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
