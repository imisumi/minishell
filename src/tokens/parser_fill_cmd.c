/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 15:45:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/13 15:51:05 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "error.h"
#include "cmd_lst.h"
#include "redir_lst.h"
#include <stdio.h>

static t_redir_type	get_redir_type(char *value)
{
	if (value[0] == '<')
	{
		if (value[1] == '<')
			return (REDIR_HERE_DOC);
		return (REDIR_INPUT);
	}
	if (value[1] == '>')
		return (REDIR_OUTPUT_APPEND);
	return (REDIR_OUTPUT);
}

static t_redir_list	*add_redirect(t_list **tokens, t_cmd_list *cmd_list)
{
	t_redir_type	type;
	char			*dupe;
	t_redir_list	*redir_node;

	type = get_redir_type(((t_token *)(*tokens)->content)->value);
	*tokens = (*tokens)->next;
	dupe = ft_strdup(((t_token *)(*tokens)->content)->value);
	if (dupe == NULL)
		return (NULL);
	redir_node = redir_lstnew_back(&cmd_list->redir, dupe, type);
	if (redir_node == NULL)
	{
		free(dupe);
		return (NULL);
	}
	return (redir_node);
}

t_error	fill_cmd(t_list **tokens, t_cmd_list *cmd_list)
{
	size_t	i;

	i = 0;
	while (*tokens != NULL && ((t_token *)(*tokens)->content)->type != PIPE)
	{
		if (((t_token *)(*tokens)->content)->type == REDIRECT)
		{
			if (add_redirect(tokens, cmd_list) == NULL)
			{
				cmd_list->args[i] = NULL;
				return (set_error(E_SYS));
			}
		}
		else
		{
			cmd_list->args[i]
				= ft_strdup(((t_token *)(*tokens)->content)->value);
			if (cmd_list->args[i] == NULL)
				return (set_error(E_SYS));
			i++;
		}
		*tokens = (*tokens)->next;
	}
	return (OK);
}
