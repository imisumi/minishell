/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstdelone.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:18:36 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/02 16:25:32 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "redir_lst.h"
#include <stdlib.h>

/**
 * Deletes a cmd list node
 * @param cmd_lst List node to be deleted
 */
void	cmd_lstdelone(t_cmd_list *cmd_lst)
{
	size_t	i;

	if (cmd_lst->args != NULL)
	{
		i = 0;
		while (cmd_lst->args[i] != NULL)
		{
			free(cmd_lst->args[i]);
			i++;
		}
		free(cmd_lst->args);
	}
	redir_lstclear(&cmd_lst->redir);
	free(cmd_lst);
}
