/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/15 12:22:18 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipe.h"

void	redir_free_list(t_redir *list)
{
	t_redir *temp;

	while (list)
	{
		temp = list->next;
		free(list->file);
		free(list);
		list = temp;
	}
}

void redir_add_back(t_cmd_list **head, t_redir *new)
{
	if ((*head)->redir == NULL)
		(*head)->redir = new;
	else
	{
		t_redir *current = (*head)->redir;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_redir	*redir_new_node()
{
	t_redir *new;

	new = calloc(sizeof(t_redir), 1);
	if (new == NULL)
		exit(1);
	new->file = NULL;
	// new->type = REDIR_PIPE;
	new->next = NULL;
	return (new);
}