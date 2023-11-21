/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi <imisumi@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 15:00:46 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/13 16:07:35 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "types.h"
#include "tokens.h"
#include "error.h"
#include "cmd_lst.h"
#include "redir_lst.h"
#include <stdio.h>

/*
	- recieves tokens
	- read tokens 1 by 1
	- decide
	- returns the command list
*/
static size_t	get_arg_count(t_list *tokens)
{
	size_t	arg_count;

	arg_count = 0;
	while (tokens != NULL && ((t_token *)tokens->content)->type != PIPE)
	{
		if (((t_token *)tokens->content)->type == REDIRECT)
			tokens = tokens->next;
		else
			arg_count++;
		tokens = tokens->next;
	}
	return (arg_count);
}

static t_cmd_list	*get_cmd(t_list **tokens)
{
	t_cmd_list	*cmd_list;
	size_t		arg_count;

	arg_count = get_arg_count(*tokens);
	cmd_list = cmd_lstnew(NULL, NULL, NULL);
	if (cmd_list == NULL)
		return (NULL);
	cmd_list->args = malloc((arg_count + 1) * sizeof(char *));
	if (cmd_list->args == NULL)
	{
		cmd_lstdelone(cmd_list);
		return (NULL);
	}
	cmd_list->args[arg_count] = NULL;
	if (fill_cmd(tokens, cmd_list) != OK)
	{
		cmd_lstdelone(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}

t_error	cmd_parser(t_data *data, t_list *tokens)
{
	t_cmd_list		*cmd_list;

	data->cmd_list = NULL;
	while (tokens != NULL)
	{
		cmd_list = get_cmd(&tokens);
		if (cmd_list == NULL)
		{
			cmd_lstclear(&cmd_list);
			return (set_error(E_SYS));
		}
		cmd_lstadd_back(&data->cmd_list, cmd_list);
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
	}
	return (OK);
}
