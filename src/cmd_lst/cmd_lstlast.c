/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstlast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 13:57:02 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:38 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

/**
 * Retrieves the last node of a cmd list
 * @param cmd_lst List to get the last node of
 * @returns The last node of the list, NULL if the list is empty
 */
t_cmd_list	*cmd_lstlast(t_cmd_list *cmd_lst)
{
	while (cmd_lst != NULL && cmd_lst->next != NULL)
	{
		cmd_lst = cmd_lst->next;
	}
	return (cmd_lst);
}
