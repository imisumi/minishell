/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_lst.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:00:08 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 14:23:09 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LST_H
# define CMD_LST_H

# include "types.h"

void		cmd_lstadd_back(t_cmd_list **cmd_lst, t_cmd_list *new);

void		cmd_lstadd_front(t_cmd_list **cmd_lst, t_cmd_list *new);

void		cmd_lstclear(t_cmd_list **cmd_lst);

void		cmd_lstdelone(t_cmd_list *cmd_lst);

t_cmd_list	*cmd_lstlast(t_cmd_list *cmd_lst);

t_cmd_list	*cmd_lstnew_back(t_cmd_list **cmd_lst, char *cmd, \
								char **args, t_redir_list *redirs);

t_cmd_list	*cmd_lstnew_front(t_cmd_list **cmd_lst, char *cmd, \
								char **args, t_redir_list *redirs);

t_cmd_list	*cmd_lstnew(char *cmd, char **args, t_redir_list *redirs);

int			cmd_lstsize(t_cmd_list *list);

#endif
