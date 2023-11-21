/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 13:17:40 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 15:07:53 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a new list node and adds it to the back of a list
 * @param lst List to be expanded
 * @param content Content of the list node to be added to lst
 * @returns The new list node, NULL on error
 */
t_list	*ft_lstnew_back(t_list **lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	ft_lstadd_back(lst, new);
	return (new);
}
