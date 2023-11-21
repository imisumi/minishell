/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstadd_back.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:19:16 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:04:30 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "redir_lst.h"

/**
 * Adds a list node to the back of a redir list
 * @param redir_lst List to be expanded
 * @param new List node to be added to lst
 */
void	redir_lstadd_back(t_redir_list **redir_lst, t_redir_list *new)
{
	if (*redir_lst == NULL)
		*redir_lst = new;
	else
		redir_lstlast(*redir_lst)->next = new;
}
