/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear_whitespace_tokens.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 17:21:21 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/09/25 17:27:14 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	clear_whitespace_tokens(t_list **tokens)
{
	while (*tokens != NULL)
	{
		if (((t_token *)((*tokens)->content))->type == WHITESPACE)
			ft_lst_dispose_one(tokens, &free_token);
		else
			tokens = &(*tokens)->next;
	}
	return (OK);
}
