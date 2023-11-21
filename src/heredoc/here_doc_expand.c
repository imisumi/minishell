/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:36:34 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/19 15:10:14 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "pipe.h"

static char	*replace_portion(char *str, int start, int end, char *replacement)
{
	int		i;
	int		result_index;
	int		r_index;
	char	*result;
	size_t	r_len;

	r_len = strlen(replacement);
	result = malloc(sizeof(char) * ft_strlen(str) - (end - start) + r_len + 1);
	if (result == NULL)
		return (NULL);
	set_int_to_zero(&i, &result_index, &r_index);
	while (str[i])
	{
		if (i >= start && i < end)
		{
			if ((size_t)r_index < r_len)
				copy_char_to_res(result, &result_index, replacement, &r_index);
			else
				i++;
		}
		else
			copy_char_to_res(result, &result_index, str, &i);
	}
	result[result_index] = '\0';
	return (free(str), result);
}

static bool	replace_exit_code(char **new_line, int i)
{
	char	*code;

	code = ft_itoa(get_exit_code());
	if (!code)
	{
		free(new_line);
		return (false);
	}
	*new_line = replace_portion(*new_line, i, i + 2, code);
	free(code);
	return (true);
}

void	replace_env_var(char *line, char **new_line, t_list *env_list, int i)
{
	int		start;
	t_env	*env;

	if (line[i] != '\0')
	{
		i++;
		start = i;
		while (line[i] != '\0' && (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
		env = get_env_var_n(env_list, &line[start], i - start);
		if (env == NULL)
			*new_line = replace_portion(*new_line, start - 1, i, "");
		else
			*new_line = replace_portion(*new_line, start - 1, i, env->value);
	}
	return ;
}

char	*expand_line(char *line, t_list *env_list)
{
	int		i;
	char	*new_line;

	new_line = ft_strdup(line);
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '$' && line[i] != '\0')
		i++;
	if (line[i] == '$' && line[i + 1] == '?')
		replace_exit_code(&new_line, i);
	else if (line[i] == '$')
		replace_env_var(line, &new_line, env_list, i);
	free(line);
	return (new_line);
}
