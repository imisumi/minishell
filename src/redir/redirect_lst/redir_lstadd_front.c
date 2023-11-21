/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstadd_front.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:19:22 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:04:38 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

/**
 * Adds a list node to the front of a redir list
 * @param redir_lst List to be expanded
 * @param new List node to be added to lst
 */
void	redir_lstadd_front(t_redir_list **redir_lst, t_redir_list *new)
{
	new->next = *redir_lst;
	*redir_lst = new;
}
