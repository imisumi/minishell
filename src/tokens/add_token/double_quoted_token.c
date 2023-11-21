/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_quoted_token.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:56:59 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:15:36 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	add_double_quoted_token(t_list **tokens, char *input, size_t *i)
{
	size_t		start;

	(*i)++;
	start = *i;
	while (input[*i] != '\0' && input[*i] != '\"')
		(*i)++;
	if (input[*i] == '\0')
		return (set_error(E_QUOTE));
	if (add_new_token(tokens, DOUBLE_QUOTED, &input[start], *i - start) != OK)
		return (get_error());
	(*i)++;
	return (OK);
}
