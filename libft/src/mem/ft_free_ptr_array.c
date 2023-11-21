/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_ptr_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 15:43:47 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:19:52 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * Calls free on every element of array, then frees the array itself
 * @param array The (NULL-terminated) array to free
 */
void	ft_free_ptr_array(void **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
