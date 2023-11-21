/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_whitepace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 16:28:41 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/04 16:29:46 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

bool	all_whitepace(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type != WHITESPACE)
			return (false);
		tokens = tokens->next;
	}
	return (true);
}
