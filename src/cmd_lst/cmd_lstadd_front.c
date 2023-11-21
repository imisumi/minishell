/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstadd_front.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:19:22 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:53 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

/**
 * Adds a list node to the front of a cmd list
 * @param cmd_lst List to be expanded
 * @param new List node to be added to lst
 */
void	cmd_lstadd_front(t_cmd_list **cmd_lst, t_cmd_list *new)
{
	new->next = *cmd_lst;
	*cmd_lst = new;
}
