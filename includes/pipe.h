/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:47:43 by rhorbach          #+#    #+#             */
/*   Updated: 2023/11/21 18:17:20 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "types.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "redir_lst.h"

# include <stdint.h>

# include "libft.h"
# include "error.h"

# define NO_READLINE 0
# define TESTING 0
# define CHILD 0
# define SET 1
# define GET 0

# define USE_ASCII_COLOR 0

# define PROMPT_SUCCESS "\033[32;1m✔ \033[34;1m ms \033[35;1m~ \033[1;36m"
# define PROMPT_FAILURE "\033[31;1m𐄂 \033[34;1m ms \033[35;1m~ \033[1;36m"
# define PROMPT_END "\033[1;34m$\033[0m "

# if USE_ASCII_COLOR
#  define HERE_DOC "\033[32;1mheredoc > \033[0m"
# else
#  define HERE_DOC "heredoc > "
# endif

# define HERE_DOC_TMP ".tmp-heredock-"
// # define HERE_DOC_TMP "/tmp/.tmp-heredock-"

# define RESET "\033[0m"

/* ************************************************************************** */
/*                  EXIT_CODE.C                                               */
void				set_exit_code(t_exit_code err);
t_exit_code			get_exit_code(void);
/* ************************************************************************** */

/* ************************************************************************** */
/*                  FREE.C   / FREE2.C                                        */
void				free_env_lst(t_list *env_lst);
void				free_eof(t_data *data);
void				free_data_utils(t_data *data);
void				free_data(t_data *data);
void				free_2d_array(char **arr);
void				free_redir_list(t_redir_list *redir);
void				free_data(t_data *data);
void				free_data_cmd(t_data *data);
void				free_cmd_lst(t_cmd_list *cmd_list);
void				free_child_data(t_data *data, char **envp, char **paths);
t_error				clean_input(t_data *data, char *prompt);
/* ************************************************************************** */

/* ************************************************************************** */
/*          BUILTIN.C                                                         */
bool				check_builtin(char *cmd);
int					builtin_exit(t_cmd_list *lst, bool printf_exit);
int					builtin_echo(t_cmd_list *lst);
int					builtin_cd(t_data *d, t_cmd_list *lst);
int					builtin_export(t_data *data, t_cmd_list *lst);
int					builtin_unset(t_data *data, t_cmd_list *lst);
/* ************************************************************************** */

/* ************************************************************************** */
/*      ENV.C                                                                 */
void				fill_env_file(t_data d);
int					print_env_lst(t_list *env_lst);
char				*get_env(char **envp, char *path);
char				**env_paths(t_list *envp);
char				*get_env_var_value(t_list *env_lst, char *name);
/* ************************************************************************** */

/* ************************************************************************** */
/*      SIGNALS.C                                                             */
void				enable_sigquit(void);
void				disable_sigquit(void);
void				enable_sigint(void);
void				enable_sigint_pipe(void);
void				enable_sigint_heredoc(void);
/* ************************************************************************** */

/* ************************************************************************** */
/*      HEREDOC.C                                                             */
bool				here_doc(t_data *data, char *heredoc);
/* ************************************************************************** */

/* ************************************************************************** */
/*      REDIR_ERROR.C                                                         */
bool				check_input_error(t_data *data, t_redir_list *temp);
bool				check_output_error(t_data *data, t_redir_list *temp, \
										int *out);
bool				check_output_eppend_error(t_data *data, t_redir_list *temp, \
												int *out);
/* ************************************************************************** */

/* ************************************************************************** */
/*      EXEC                                                                  */
int					exec_error_msg(char	*cmd, char **paths);
int					exec_cmd(t_data *data, t_cmd_list *lst);
/* ************************************************************************** */

int					ft_strcmp(const char *s1, const char *s2);

bool				check_redir_list(t_data *data, t_cmd_list *lst);

char				*get_prompt(void);

//! env
t_list				*ft_lstnew(void *content);

t_error				init_env_lst(t_data *data, char **envp);
t_error				set_env_var_composite(t_list **env_lst, char *env);
t_env				*get_env_var(t_list *env_lst, char *name);
t_env				*get_env_var_n(t_list *env_lst, char *name, size_t n);
t_error				set_env_var(t_list **env_lst, char *name, char *value);
t_error				add_env_var(t_list **env_lst, char *name, \
									char *duped_value);
void				print_export_lst(t_list *env_lst);
char				**env_list_to_array(t_list *env_list);
void				unset_env_var(t_list **env_lst, char *name);

// here doc

char				*expand_line(char *line, t_list *env_list);
int					exit_code_count(char *line);
int					random_digit(int fd);
char				*generate_random_numbers(int length);
void				copy_char_to_res(char *result, int *result_index, \
										char *str, int *i);
void				set_int_to_zero(int *i, int *j, int *k);

// utils.c
char				*find_path(char *cmd, char **paths);
int					fd_put_err(char *input, char *msg, int ret);
t_error				set_old_pwd(t_data *data);

// utils2.c
bool				is_only_whitespace(char *str);

// pipe.c
t_error				pipex(t_data *data);

void				run_single_builtin(t_data *data, t_cmd_list *lst);
int					run_pipe_builtin(t_data *d, t_cmd_list *lst);

t_utils				init_utils(void);

int					storage(int value, int flag);



#endif
