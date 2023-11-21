/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstnew_back.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:16:55 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:07:15 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "redir_lst.h"

/**
 * Creates a new list node and adds it to the back of a redir list
 * @param redir_lst List to be expanded
 * @param file file to be redirected to
 * @param type the type of redirect to be used
 * @returns The new list node, NULL on error
 */
t_redir_list	*redir_lstnew_back(t_redir_list **redir_lst, char *file, \
									t_redir_type type)
{
	t_redir_list	*new;

	new = redir_lstnew(file, type);
	if (new == NULL)
		return (NULL);
	redir_lstadd_back(redir_lst, new);
	return (new);
}
