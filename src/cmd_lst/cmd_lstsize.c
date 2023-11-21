/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstsize.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 14:21:57 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 14:23:50 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

int	cmd_lstsize(t_cmd_list *list)
{
	int	size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}
