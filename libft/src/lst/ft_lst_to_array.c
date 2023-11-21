/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_to_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 15:21:18 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:20:24 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * Converts a list to an array
 * @param lst List to be converted
 * @returns A NULL-terminated array, or NULL on error
 */
void	**ft_lst_to_array(t_list *lst)
{
	void	**array;
	int		list_size;
	int		i;

	list_size = ft_lstsize(lst);
	array = malloc((list_size + 1) * sizeof(void *));
	if (array == NULL)
		return (NULL);
	array[list_size] = NULL;
	i = 0;
	while (lst != NULL)
	{
		array[i] = lst->content;
		lst = lst->next;
		i++;
	}
	return (array);
}
