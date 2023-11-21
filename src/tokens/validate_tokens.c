/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:00:59 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/18 15:41:13 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokens.h"
#include "types.h"
#include "error.h"
#include "stdio.h"

static t_error	is_valid_pipe(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL \
	&& ((t_token *)(tokens->content))->type != PIPE)
	{
		if (((t_token *)(tokens->content))->type != WHITESPACE)
			return (OK);
		tokens = tokens->next;
	}
	return (set_error(E_INVAL_PIPE));
}

static t_error	is_valid_redir(t_list *tokens)
{
	tokens = tokens->next;
	while (tokens != NULL \
	&& ((t_token *)(tokens->content))->type != PIPE \
	&& ((t_token *)(tokens->content))->type != REDIRECT)
	{
		if (((t_token *)(tokens->content))->type != WHITESPACE)
			return (OK);
		tokens = tokens->next;
	}
	return (set_error(E_INVAL_REDIR));
}

t_error	validate_tokens(t_list *tokens)
{
	bool	valid;

	valid = false;
	while (tokens != NULL)
	{
		if (((t_token *)(tokens->content))->type != WHITESPACE && \
			((t_token *)(tokens->content))->type != PIPE)
			valid = true;
		if (((t_token *)(tokens->content))->type == PIPE)
		{
			if (valid == false)
				return (set_error(E_INVAL_PIPE));
			if (is_valid_pipe(tokens) != OK)
				return (get_error());
		}
		else if (((t_token *)(tokens->content))->type == REDIRECT)
		{
			if (is_valid_redir(tokens) != OK)
				return (get_error());
		}
		tokens = tokens->next;
	}
	return (OK);
}
