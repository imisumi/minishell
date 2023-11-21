/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstclear.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:21:12 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:57 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "cmd_lst.h"

/**
 * Clears a cmd list
 * @param cmd_lst List to be cleared
 */
void	cmd_lstclear(t_cmd_list **cmd_lst)
{
	t_cmd_list	*temp;

	while (*cmd_lst != NULL)
	{
		temp = (*cmd_lst)->next;
		cmd_lstdelone(*cmd_lst);
		*cmd_lst = temp;
	}
	*cmd_lst = NULL;
}
