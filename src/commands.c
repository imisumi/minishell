/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/20 19:49:08 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"

void	temp_cmd(t_cmd_list **lst, char *cmd, char **args)
{
	*lst = create_cmd_list(cmd, args);
}

void	temp_cmd_pipe(t_cmd_list **lst, char **arg1, char **arg2)
{
	t_cmd_list	*new_cmd;

	*lst = create_cmd_list(arg1[0], arg1);
	new_cmd = create_cmd_list(arg2[0], arg2);
	cmd_list_add_back(lst, new_cmd);
}
