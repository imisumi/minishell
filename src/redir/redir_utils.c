/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:18 by rhorbach          #+#    #+#             */
/*   Updated: 2023/11/21 17:29:53 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

bool	do_redir(t_data *data, int *fd, t_redir_list *temp, int *out)
{
	if (temp->file[0] == '\0')
	{
		fd_put_err(NULL, "No such file or directory\n", 1);
		set_exit_code(1);
		return (false);
	}
	if (temp->type == REDIR_INPUT)
	{
		fd[0] = open(temp->file, O_RDONLY);
		if (check_input_error(data, temp) == true)
			return (false);
	}
	if (temp->type == REDIR_OUTPUT)
	{
		fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (check_output_error(data, temp, out) == true)
			return (false);
	}
	if (temp->type == REDIR_OUTPUT_APPEND)
	{
		fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (check_output_eppend_error(data, temp, out) == true)
			return (false);
	}
	return (true);
}

int	do_pipe(int *fd)
{
	int	fd_pipe[2];

	// if (fd[0] >= 0)
	// 	close(fd[0]);
	pipe(fd_pipe);
	fd[1] = fd_pipe[1];
	fd[0] = fd_pipe[0];
	dup2(fd_pipe[1], fd[1]);
	dup2(fd_pipe[0], fd[0]);
	return (1);
}

bool	check_heredoc(t_data *data, t_cmd_list *lst)
{
	t_redir_list	*temp;
	bool			redir;

	temp = lst->redir;
	redir = true;
	storage(0, SET);
	enable_sigint_heredoc();
	while (temp)
	{
		if (storage(0, GET) == 1)
			return (false);
		if (temp->type == REDIR_HERE_DOC)
		{
			redir = here_doc(data, temp->file);
		}
		temp = temp->next;
	}
	return (redir);
}

bool	find_redirections(t_data *data, t_cmd_list *lst, int *out, int *pip)
{
	t_redir_list	*temp;

	temp = lst->redir;
	while (temp)
	{
		if (temp->type == REDIR_INPUT || temp->type == REDIR_OUTPUT \
				|| temp->type == REDIR_OUTPUT_APPEND)
		{
			if (do_redir(data, data->utils.fd, temp, out) == false)
			{
				if (out == 0 && lst->next != NULL)
					*pip = do_pipe(data->utils.fd);
				return (false);
			}
		}
		temp = temp->next;
	}
	return (true);
}

bool	check_redir_list(t_data *data, t_cmd_list *lst)
{
	int				out;
	int				pip;

	out = 0;
	pip = 0;
	dup2(data->utils.fd[0], STDIN_FILENO);
	if (check_heredoc(data, lst) == false)
		return (enable_sigint(), false);
	enable_sigint();
	if (find_redirections(data, lst, &out, &pip) == false)
		return (false);
	if (out == 0 && lst->next != NULL)
		pip = do_pipe(data->utils.fd);
	if (out == 0 && pip == 0)
		data->utils.fd[1] = dup(data->utils.fd[3]);
	return (true);
}
