/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_lst.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:00:08 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/16 15:00:42 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_LST_H
# define REDIR_LST_H

# include "types.h"

void			redir_lstadd_back(t_redir_list **redir_lst, t_redir_list *new);

void			redir_lstadd_front(t_redir_list **redir_lst, t_redir_list *new);

void			redir_lstclear(t_redir_list **redir_lst);

void			redir_lstdelone(t_redir_list *redir_lst);

t_redir_list	*redir_lstlast(t_redir_list *redir_lst);

t_redir_list	*redir_lstnew_back(t_redir_list **redir_lst, char *file, \
								t_redir_type type);

t_redir_list	*redir_lstnew_front(t_redir_list **redir_lst, char *file, \
								t_redir_type type);

t_redir_list	*redir_lstnew(char *file, t_redir_type type);

#endif
