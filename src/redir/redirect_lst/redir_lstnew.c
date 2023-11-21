/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:19:40 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/09/06 17:35:16 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdlib.h>

/**
 * Creates a new redir list node and fills it with content
 * @param file file to be redirected to
 * @param type	the type of redirect to be used
 * @returns The new list node, NULL on error
 */
t_redir_list	*redir_lstnew(char *file, t_redir_type type)
{
	t_redir_list	*new_redir_list;

	new_redir_list = malloc(sizeof(t_redir_list));
	if (new_redir_list == NULL)
		return (NULL);
	new_redir_list->file = file;
	new_redir_list->type = type;
	new_redir_list->next = NULL;
	return (new_redir_list);
}
