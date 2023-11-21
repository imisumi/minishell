/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstclear.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:01:00 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:04:43 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "redir_lst.h"

/**
 * Clears a redir list
 * @param redir_lst List to be cleared
 */
void	redir_lstclear(t_redir_list **redir_lst)
{
	t_redir_list	*temp;

	while (*redir_lst != NULL)
	{
		temp = (*redir_lst)->next;
		redir_lstdelone(*redir_lst);
		*redir_lst = temp;
	}
	*redir_lst = NULL;
}
