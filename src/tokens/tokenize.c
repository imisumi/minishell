/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 15:03:56 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/02 14:48:39 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "tokens.h"
#include "types.h"
#include "error.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	free(token->value);
	free(token);
}

__attribute__((warn_unused_result))
t_token	*create_new_token(t_token_type token_type,
						char *input, size_t start, size_t len)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = ft_substr(input, start, len);
	if (token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = token_type;
	return (token);
}

__attribute__((warn_unused_result))
t_error	add_new_token(t_list **tokens, t_token_type token_type,
						char *input, size_t len)
{
	t_token		*token;

	token = create_new_token(token_type, input, 0, len);
	if (token == NULL)
		return (set_error(E_SYS));
	if (ft_lstnew_back(tokens, token) == NULL)
	{
		free_token(token);
		return (set_error(E_SYS));
	}
	return (OK);
}

t_error	call_jumping_table(t_list **tokens, char *input, size_t *i)
{
	static const t_add_token_fn	jump_table[] = {
	[' '] = &add_space_token,
	['\t'] = &add_space_token,
	['\n'] = &add_space_token,
	['\v'] = &add_space_token,
	['\f'] = &add_space_token,
	['\r'] = &add_space_token,
	['>'] = &add_redirect_token,
	['<'] = &add_redirect_token,
	['|'] = &add_pipe_token,
	['\''] = &add_single_quoted_token,
	['\"'] = &add_double_quoted_token,
	};

	if (ft_strchr(" \t\n\v\f\r><|\'\"", input[*i]) != NULL)
		return (jump_table[(size_t)input[*i]](tokens, input, i));
	return (add_word_token(tokens, input, i));
}

__attribute__((warn_unused_result))
t_error	tokenize(t_list **tokens, char *input)
{
	size_t		i;

	i = 0;
	while (input[i] != '\0')
	{
		if (call_jumping_table(tokens, input, &i) != OK)
			return (get_error());
	}
	return (OK);
}
