/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_dispose_one.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:18:36 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/09/19 17:00:29 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * Cleanly disposes of a list node
 * @param lst List node to be disposed
 * @param del The function that is called to clear the node's content,
 * may be NULL
 */
void	ft_lst_dispose_one(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	next = (*lst)->next;
	ft_lstdelone(*lst, del);
	*lst = next;
}
