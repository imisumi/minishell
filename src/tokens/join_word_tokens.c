/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   join_word_tokens.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 13:17:47 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/12 13:52:55 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "types.h"
#include "tokens.h"

bool	is_wordlike(t_token *token)
{
	return (token->type == WORD
		|| token->type == SINGLE_QUOTED
		|| token->type == DOUBLE_QUOTED);
}

static size_t	get_joined_str_len(t_list *tokens)
{
	size_t	joined_str_len;

	joined_str_len = 0;
	while (tokens != NULL && is_wordlike(tokens->content))
	{
		joined_str_len += ft_strlen(((t_token *)(tokens->content))->value);
		tokens = tokens->next;
	}
	return (joined_str_len);
}

static t_error	join_words(t_list **tokens)
{
	size_t	joined_str_len;
	char	*joined_str;

	joined_str_len = get_joined_str_len(*tokens);
	joined_str = malloc((joined_str_len + 1) * sizeof(char));
	if (joined_str == NULL)
		return (set_error(E_SYS));
	joined_str[0] = '\0';
	ft_strlcat(joined_str,
		((t_token *)((*tokens)->content))->value, joined_str_len + 1);
	free(((t_token *)((*tokens)->content))->value);
	((t_token *)((*tokens)->content))->value = joined_str;
	tokens = &(*tokens)->next;
	while (*tokens != NULL && is_wordlike((*tokens)->content))
	{
		ft_strlcat(joined_str,
			((t_token *)((*tokens)->content))->value, joined_str_len + 1);
		ft_lst_dispose_one(tokens, &free_token);
	}
	return (OK);
}

t_error	join_word_tokens(t_list **tokens)
{
	while (*tokens != NULL && (*tokens)->next != NULL)
	{
		if (is_wordlike((*tokens)->content))
		{
			((t_token *)((*tokens)->content))->type = WORD;
			if (is_wordlike((*tokens)->next->content))
			{
				if (join_words(tokens) != OK)
					return (get_error());
			}
		}
		tokens = &(*tokens)->next;
	}
	return (OK);
}
