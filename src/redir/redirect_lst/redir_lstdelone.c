/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lstdelone.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:01:16 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:04:45 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "redir_lst.h"
#include <stdlib.h>

/**
 * Deletes a redir list node
 * @param redir_lst List node to be deleted
 */
void	redir_lstdelone(t_redir_list *redir_lst)
{
	free(redir_lst->file);
	free(redir_lst);
}
