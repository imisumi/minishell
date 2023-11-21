/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:18:36 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:53:25 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * Deletes a list node
 * @param lst List node to be deleted
 * @param del The function that is called to clear the node's content,
 * may be NULL
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del != NULL)
		(*del)(lst->content);
	free(lst);
}
