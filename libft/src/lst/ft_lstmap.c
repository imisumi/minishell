/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 13:28:07 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 15:03:36 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Duplicates a list and transforms its content using f
 * @param lst List to be duplicated
 * @param f The function that is called to transform each node's content
 * @param del The function that is called to clear each node's content,
 * may be NULL
 * @returns The new transformed list, NULL on error
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*newlst;
	void	*content;

	newlst = NULL;
	while (lst != NULL)
	{
		content = (*f)(lst->content);
		newnode = ft_lstnew(content);
		if (newnode == NULL)
		{
			(*del)(content);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
