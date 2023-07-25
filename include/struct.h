/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:39:57 by imisumi-wsl       #+#    #+#             */
/*   Updated: 2023/07/25 13:21:29 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef enum s_redir_type
{
	REDIR_PIPE = 0,
	REDIR_INPUT = 1,
	REDIR_OUTPUT = 2,
	REDIR_INPUT_APPEND = 3,
	REDIR_OUTPUT_APPEND = 4
}	t_redir_type;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	struct s_redir	*next;
}	t_redir;


typedef struct s_cmd_list
{
	char				*cmd;
	char				**args;
	t_redir				*redir;

	struct s_cmd_list	*next;
}	t_cmd_list;

typedef struct s_data
{
	t_cmd_list	*cmd_list;
}	t_data;

#endif // STRUCT_H