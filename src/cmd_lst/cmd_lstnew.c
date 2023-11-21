/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:19:40 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/17 16:12:44 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdlib.h>

/**
 * Creates a new cmd list node and fills it with content
 * @param cmd absolute path of cmd to be contained within the cmd list node
 * @param args cmd and its args to be contained within the cmd list node
 * @param redirs redirection list to be contained within the cmd list node
 * @returns The new list node, NULL on error
 */
t_cmd_list	*cmd_lstnew(char *cmd, char **args, t_redir_list *redirs)
{
	t_cmd_list	*new_cmd_list;

	new_cmd_list = malloc(sizeof(t_cmd_list));
	if (new_cmd_list == NULL)
		return (NULL);
	(void)cmd;
	new_cmd_list->args = args;
	new_cmd_list->redir = redirs;
	new_cmd_list->next = NULL;
	return (new_cmd_list);
}
