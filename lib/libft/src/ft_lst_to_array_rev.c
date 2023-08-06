/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_to_array_rev.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 15:21:18 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/06/07 15:29:11 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	**ft_lst_to_array_rev(t_list *lst)
{
	void	**array;
	int		list_size;
	int		i;

	list_size = ft_lstsize(lst);
	array = malloc((list_size + 1) * sizeof(void *));
	if (array == NULL)
		return (NULL);
	array[list_size] = NULL;
	i = list_size;
	while (lst != NULL)
	{
		i--;
		array[i] = lst->content;
		lst = lst->next;
	}
	return (array);
}
