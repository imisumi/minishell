/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:35:16 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/18 15:39:49 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "tokens.h"
#include "types.h"
#include "error.h"
#include "env.h"
#include "pipe.h"

// TODO: place in libft?
static char	*replace(char *str, size_t start, size_t len, char *replacee)
{
	char	*value;
	size_t	left_len;
	size_t	middle_len;
	size_t	right_len;

	left_len = start;
	middle_len = ft_strlen(replacee);
	right_len = ft_strlen(&str[start + len]);
	value = malloc((left_len + middle_len + right_len + 1) * sizeof(char));
	if (value == NULL)
		return (NULL);
	value[left_len + middle_len + right_len] = '\0';
	ft_memcpy(value, str, left_len);
	ft_memcpy(&value[left_len], replacee, middle_len);
	ft_memcpy(&value[left_len + middle_len], &str[start + len], right_len);
	return (value);
}

static t_error	expand_token_part(t_token *token, size_t start,
									size_t *i, t_env *env)
{
	char	*replaced;

	if (env == NULL || env->value == NULL)
		replaced = replace(token->value, start, *i - start, "");
	else
		replaced = replace(token->value, start, *i - start, env->value);
	if (replaced == NULL)
		return (set_error(E_SYS));
	free(token->value);
	token->value = replaced;
	if (env != NULL && env->value != NULL)
		*i = start + ft_strlen(env->value);
	else
		*i = start;
	return (OK);
}

static t_error	expand_token_part_exit_status(t_token *token, size_t start,
												size_t *i)
{
	char	*replaced;
	char	*error_code_str;

	error_code_str = ft_itoa(get_exit_code());
	if (error_code_str == NULL)
		return (set_error(E_SYS));
	replaced = replace(token->value, start, *i - start, error_code_str);
	if (replaced == NULL)
	{
		free(error_code_str);
		return (set_error(E_SYS));
	}
	free(token->value);
	token->value = replaced;
	*i = start + ft_strlen(error_code_str);
	free(error_code_str);
	return (OK);
}

static size_t	get_var_name_len(t_token *token, size_t start)
{
	size_t	i;

	i = start;
	if (token->value[i] == '?')
	{
		i++;
		return (i - start);
	}
	while (token->value[i] != '\0' && \
			(ft_isalnum(token->value[i]) || token->value[i] == '_'))
		i++;
	return (i - start);
}

t_error	expand_token_variable(t_token *token, t_list *env_lst, size_t *i)
{
	size_t	start;
	size_t	len;
	t_env	*env;

	start = *i;
	len = get_var_name_len(token, start);
	*i += len;
	if (len == 0)
		return (OK);
	if (len == 1 && token->value[start] == '?')
		return (expand_token_part_exit_status(token, start - 1, i));
	env = get_env_var_n(env_lst, &token->value[start], len);
	return (expand_token_part(token, start - 1, i, env));
}
