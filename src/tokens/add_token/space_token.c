/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   space_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:58:17 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:15:22 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	add_space_token(t_list **tokens, char *input, size_t *i)
{
	size_t		start;

	start = *i;
	while (input[*i] != '\0' && ft_isspace(input[*i]))
		(*i)++;
	if (add_new_token(tokens, WHITESPACE, &input[start], *i - start) != OK)
		return (get_error());
	return (OK);
}
