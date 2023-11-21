/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:11:25 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/18 16:38:39 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokens.h"
#include "types.h"
#include "error.h"
#include "stdio.h"

static bool	is_ambiguous(t_list **tokens)
{
	size_t	i;

	while (*tokens != NULL && is_wordlike((*tokens)->content))
	{
		if (((t_token *)((*tokens)->content))->type == WORD)
		{
			i = 0;
			if (((t_token *)((*tokens)->content))->value[0] == '\0')
				return (true);
			while (((t_token *)((*tokens)->content))->value[i] != '\0')
			{
				if (ft_isspace(((t_token *)((*tokens)->content))->value[i]))
					return (true);
				i++;
			}
		}
		*tokens = (*tokens)->next;
	}
	return (false);
}

t_error	ambiguous_redirect(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (((t_token *)(tokens->content))->type == REDIRECT)
		{
			tokens = tokens->next;
			while (tokens != NULL && \
					((t_token *)(tokens->content))->type == WHITESPACE)
				tokens = tokens->next;
			if (tokens != NULL && is_ambiguous(&tokens))
				return (set_error(E_AMBIGUOUS_REDIRECT));
		}
		else
			tokens = tokens->next;
	}
	return (OK);
}
