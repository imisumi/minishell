/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:58:20 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/23 15:48:18 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>

typedef enum s_exit_code
{
	SUCCESS = 0,
	FAILURE = 1,
	NOT_EXECUTABLE = 126,
	NOT_FOUND = 127,
	ARGUMENT_ERROR = 128,
	CONTROL_C_TERMINATED = 130,
	NOT_RECOVERABLE = 131
}	t_exit_code;

typedef enum e_error
{
	OK,
	E_SYS,
	E_QUOTE,
	E_INVAL_PIPE,
	E_INVAL_REDIR,
	E_AMBIGUOUS_REDIRECT
}					t_error;

/*----------------------------------------------------------------------------*/

typedef struct s_env {
	char	*name;
	char	*value;
}	t_env;

/*----------------------------------------------------------------------------*/

typedef enum s_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_HERE_DOC,
	REDIR_OUTPUT_APPEND
}					t_redir_type;

typedef struct s_redir //should be the same as token- HAHAHAH NO
{
	char			*file;
	t_redir_type	type;
	struct s_redir	*next;
}					t_redir_list;

/*----------------------------------------------------------------------------*/

typedef enum e_token_type {
	PIPE,
	REDIRECT,
	WHITESPACE,
	WORD,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
}					t_token_type;

typedef struct s_token {
	char			*value;
	t_token_type	type;
}					t_token;

/*----------------------------------------------------------------------------*/

//! *cmd; //replace with absolute path
//! **args; //argv[0], NULL terminated
//! *redir; //list of redirects, last one counts
typedef struct s_cmd_list //final assembly of the tokens in true form
{
	char				**args;
	t_redir_list		*redir;
	struct s_cmd_list	*next;
}					t_cmd_list;

typedef struct s_utils
{
	char		*local_dir;
	int			cmd_nums;
	pid_t		*child_pids;
	int			fd[4];
	char		*heredoc;
}	t_utils;

typedef struct s_data
{
	t_cmd_list		*cmd_list;
	t_list			*env_lst;
	t_utils			utils;
}					t_data;

/*----------------------------------------------------------------------------*/

typedef t_error	(*t_add_token_fn)(t_list **, char *, size_t *);

#endif
