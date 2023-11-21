/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:55:55 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/17 16:09:07 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "tokens.h"
#include "error.h"

/*
	1. check for validity (double pipes with nothing in between) 
		|| (empty tokens) etc. - DONE
	2. expand expandible variables - DONE
	3. redirect names (ambiguous redirect)
	4. fix unquoted (split unquoted) 
		((handle in join words/ whitespaces)) - DONE
	5. join words (that I am certain can be joined) - DONE
	6. remove whitespaces - DONE
	7. parse
*/

void				set_exit_code(t_exit_code err);

t_error	complete_tokens(t_list **tokens, t_list *env_lst)
{
	if (validate_tokens(*tokens) != OK || \
		expand_tokens(tokens, env_lst) != OK || \
		ambiguous_redirect(*tokens) != OK || \
		split_tokens(tokens) != OK || \
		join_word_tokens(tokens) != OK || \
		clear_whitespace_tokens(tokens) != OK)
		return (get_error());
	return (OK);
}
