/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 15:57:31 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/18 14:52:10 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "types.h"
#include "error.h"

static t_error	expand_token(t_token *token, t_list *env_lst)
{
	size_t	i;

	i = 0;
	while (token->value[i] != '\0')
	{
		while (token->value[i] != '$' && token->value[i] != '\0')
			i++;
		if (token->value[i] != '\0')
		{
			i++;
			expand_token_variable(token, env_lst, &i);
		}
	}
	return (OK);
}

t_error	expand_tokens(t_list **tokens, t_list *env_lst)
{
	while (*tokens != NULL)
	{
		if (((t_token *)((*tokens)->content))->type == REDIRECT \
		&& ft_strcmp(((t_token *)((*tokens)->content))->value, "<<") == 0)
		{
			tokens = &(*tokens)->next;
			while (*tokens != NULL \
			&& ((t_token *)((*tokens)->content))->type == WHITESPACE)
				tokens = &(*tokens)->next;
			while (*tokens != NULL && is_wordlike((*tokens)->content))
				tokens = &(*tokens)->next;
			continue ;
		}
		if (((t_token *)((*tokens)->content))->type == WORD \
		|| ((t_token *)((*tokens)->content))->type == DOUBLE_QUOTED)
		{
			if (expand_token((t_token *)((*tokens)->content), env_lst) != OK)
				return (get_error());
		}
		tokens = &(*tokens)->next;
	}
	return (OK);
}
