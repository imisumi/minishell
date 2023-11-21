/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstlast.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:01:25 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:04:48 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

/**
 * Retrieves the last node of a redir list
 * @param redir_lst List to get the last node of
 * @returns The last node of the list, NULL if the list is empty
 */
t_redir_list	*redir_lstlast(t_redir_list *redir_lst)
{
	while (redir_lst != NULL && redir_lst->next != NULL)
	{
		redir_lst = redir_lst->next;
	}
	return (redir_lst);
}
