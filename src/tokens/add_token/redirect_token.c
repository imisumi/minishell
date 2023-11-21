/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_token.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:57:37 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:15:28 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	add_redirect_token(t_list **tokens, char *input, size_t *i)
{
	size_t		start;

	start = *i;
	if (input[*i + 1] == input[*i])
		*i += 2;
	else
		*i += 1;
	if (add_new_token(tokens, REDIRECT, &input[start], *i - start) != OK)
		return (get_error());
	return (OK);
}
