/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_quoted_token.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:57:47 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:15:25 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	add_single_quoted_token(t_list **tokens, char *input, size_t *i)
{
	size_t		start;

	(*i)++;
	start = *i;
	while (input[*i] != '\0' && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\0')
		return (set_error(E_QUOTE));
	if (add_new_token(tokens, SINGLE_QUOTED, &input[start], *i - start) != OK)
		return (get_error());
	(*i)++;
	return (OK);
}
