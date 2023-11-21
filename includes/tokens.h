/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 15:11:50 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/13 16:07:23 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stdlib.h>
# include "types.h"

// tokens/add_token/space_token.c
t_error	add_space_token(t_list **tokens, char *input, size_t *i);

// tokens/add_token/redirect_token.c
t_error	add_redirect_token(t_list **tokens, char *input, size_t *i);

// tokens/add_token/pipe_token.c
t_error	add_pipe_token(t_list **tokens, char *input, size_t *i);

// tokens/add_token/single_quoted_token.c
t_error	add_single_quoted_token(t_list **tokens, char *input, size_t *i);

// tokens/add_token/double_quoted_token.c
t_error	add_double_quoted_token(t_list **tokens, char *input, size_t *i);

// tokens/add_token/word_token.c
t_error	add_word_token(t_list **tokens, char *input, size_t *i);

// tokens/tokenize.c
void	free_token(void *ptr);
t_token	*create_new_token(t_token_type token_type, \
						char *input, size_t start, size_t len);
t_error	add_new_token(t_list **tokens, t_token_type token_type, \
						char *input, size_t len);
t_error	call_jumping_table(t_list **tokens, char *input, size_t *i);
t_error	tokenize(t_list **tokens, char *input);

// tokens/all_whitepace.c
bool	all_whitepace(t_list *tokens);

// tokens/validate_tokens.c
t_error	validate_tokens(t_list *tokens);

// tokens/expand_token_variable.c
t_error	expand_token_variable(t_token *token, t_list *env_lst, size_t *i);

// tokens/expand_tokens.c
t_error	expand_tokens(t_list **tokens, t_list *env_lst);

// tokens/ambiguous_redirect.c
t_error	ambiguous_redirect(t_list *tokens);

// tokens/split_tokens.c
t_error	split_tokens(t_list **tokens);

// tokens/join_word_tokens.c
bool	is_wordlike(t_token *token);
t_error	join_word_tokens(t_list **tokens);

// tokens/clear_whitespace_tokens.c
t_error	clear_whitespace_tokens(t_list **tokens);

// tokens/complete_tokens.c
t_error	complete_tokens(t_list **tokens, t_list *env_lst);

// tokens/parser_fill_cmd.c
t_error	fill_cmd(t_list **tokens, t_cmd_list *cmd_list);

// tokens/parser.c
t_error	cmd_parser(t_data *data, t_list *tokens);

#endif
