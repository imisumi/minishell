/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:18 by rhorbach          #+#    #+#             */
/*   Updated: 2023/08/10 16:10:19 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
