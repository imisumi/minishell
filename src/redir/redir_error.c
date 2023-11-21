/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:18 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/18 17:06:36 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

bool	check_input_error(t_data *data, t_redir_list *temp)
{
	if (data->utils.fd[0] == -1)
	{
		if (access(temp->file, F_OK) == 0 && access(temp->file, R_OK) != 0)
			fd_put_err(temp->file, ": Permission denied\n", 1);
		else
			fd_put_err(temp->file, ": No such file or directory\n", 1);
		set_exit_code(1);
		dup2(data->utils.fd[3], STDIN_FILENO);
		return (true);
	}
	dup2(data->utils.fd[0], STDIN_FILENO);
	close(data->utils.fd[0]);
	return (false);
}

bool	check_output_error(t_data *data, t_redir_list *temp, int *out)
{
	if (data->utils.fd[1] == -1)
	{
		if (access(temp->file, W_OK) != 0)
			fd_put_err(temp->file, ": Permission denied\n", 1);
		else
			fd_put_err(temp->file, ": No such file or directory\n", 1);
		set_exit_code(1);
		return (true);
	}
	*out = 1;
	return (false);
}

bool	check_output_eppend_error(t_data *data, t_redir_list *temp, int *out)
{
	if (data->utils.fd[1] == -1)
	{
		if (access(temp->file, W_OK) != 0)
			fd_put_err(temp->file, ": Permission denied\n", 1);
		else
			fd_put_err(temp->file, ": No such file or directory\n", 1);
		set_exit_code(1);
		return (true);
	}
	*out = 1;
	return (false);
}
