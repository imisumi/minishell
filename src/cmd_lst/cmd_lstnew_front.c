/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lstnew_front.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:19:35 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:03:16 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "cmd_lst.h"

/**
 * Creates a new list node and adds it to the front of a cmd list
 * @param cmd_lst List to be expanded
 * @param cmd absolute path of cmd to be contained within the cmd list node
 * @param args cmd and its args to be contained within the cmd list node
 * @param redirs redirection list to be contained within the cmd list node
 * @returns The new list node, NULL on error
 */
t_cmd_list	*cmd_lstnew_front(t_cmd_list **cmd_lst, char *cmd, \
								char **args, t_redir_list *redirs)
{
	t_cmd_list	*new;

	new = cmd_lstnew(cmd, args, redirs);
	if (new == NULL)
		return (NULL);
	cmd_lstadd_front(cmd_lst, new);
	return (new);
}
