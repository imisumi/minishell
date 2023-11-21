/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_token.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:57:25 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:15:32 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	add_pipe_token(t_list **tokens, char *input, size_t *i)
{
	size_t		start;

	start = *i;
	(*i)++;
	if (add_new_token(tokens, PIPE, &input[start], *i - start) != OK)
		return (get_error());
	return (OK);
}
