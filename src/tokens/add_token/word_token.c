/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_token.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:58:01 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:15:19 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

t_error	add_word_token(t_list **tokens, char *input, size_t *i)
{
	size_t		start;

	start = *i;
	while (input[*i] != '\0' && !ft_isspace(input[*i]) \
	&& ft_strchr("|<>\"'", input[*i]) == NULL)
		(*i)++;
	if (add_new_token(tokens, WORD, &input[start], *i - start) != OK)
		return (get_error());
	return (OK);
}
