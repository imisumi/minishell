/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:03:46 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/09/19 17:23:37 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "tokens.h"
#include "error.h"

// "hello world"

// left space | right space | is boundary
// true       | true		 | false
// true       | false		 | true
// false      | true		 | true
// false      | false		 | false

static size_t	get_next_boundary(char *value, size_t i)
{
	while (value[i] != '\0'
		&& ft_isspace(value[i - 1]) == ft_isspace(value[i]))
		i++;
	return (i);
}

static t_error	split_token(t_token *token, t_list ***tokens)
{
	size_t	i;
	size_t	start;
	t_token	*new_token;

	i = 0;
	while (token->value[i] != '\0')
	{
		start = i;
		i = get_next_boundary(token->value, i + 1);
		if (ft_isspace(token->value[start]))
			new_token = create_new_token(WHITESPACE, \
											token->value, start, i - start);
		else
			new_token = create_new_token(WORD, token->value, start, i - start);
		if (new_token == NULL)
			return (set_error(E_SYS));
		if (ft_lstnew_front(*tokens, new_token) == NULL)
		{
			free_token(new_token);
			return (set_error(E_SYS));
		}
		*tokens = &(**tokens)->next;
	}
	ft_lst_dispose_one(*tokens, &free_token);
	return (OK);
}

t_error	split_tokens(t_list **tokens)
{
	while (*tokens != NULL)
	{
		if (((t_token *)((*tokens)->content))->type == WORD)
		{
			if (split_token((t_token *)((*tokens)->content), &tokens) != OK)
				return (get_error());
		}
		else
			tokens = &(*tokens)->next;
	}
	return (OK);
}

/*
1. first, I check if all pipes and redirects are followed by logical statements
2. then I expand variables that can be expanded,
3.
*/
