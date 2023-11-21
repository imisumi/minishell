/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstadd_back.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:19:16 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:42 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "cmd_lst.h"

/**
 * Adds a list node to the back of a cmd list
 * @param cmd_lst List to be expanded
 * @param new List node to be added to lst
 */
void	cmd_lstadd_back(t_cmd_list **cmd_lst, t_cmd_list *new)
{
	if (*cmd_lst == NULL)
		*cmd_lst = new;
	else
		cmd_lstlast(*cmd_lst)->next = new;
}
