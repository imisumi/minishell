/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:18 by rhorbach          #+#    #+#             */
/*   Updated: 2023/08/20 14:45:53 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"

void check_redir(t_redir *redir, int fd[])
{
	t_redir *temp = redir;
	while (temp)
	{
		temp = temp->next;
	}
	fd[1] = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// fd[1] = dup(fd[3]);
	return ;
}

void print_redir_list(t_redir *lst)
{
	t_redir	*temp;

	temp = lst;
	while (temp)
	{
		printf("type: %u\n", temp->type);
		printf("file: %s\n", temp->file);
		printf("next: %p\n", temp->next);
		printf("\n");
		temp = temp->next;
	}
}

// bool	do_redir(t_redir *temp, int *fd, int *out)
// {
// 	if(temp->type == REDIR_INPUT)
// 	{
// 		fd[0] = open(temp->file, O_RDONLY);
// 		if (fd[0] == -1)
// 		{
// 			perror(temp->file);
// 			return false;
// 		}
// 		dup2(fd[0], STDIN_FILENO);
// 	}
// 	if (temp->type == REDIR_OUTPUT)
// 	{
// 		fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd[1] == -1)
// 		{
// 			perror(temp->file);
// 			return false;
// 		}
// 		*out = 1;
// 	}
// 	if (temp->type == REDIR_OUTPUT_APPEND)
// 	{
// 		fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND);
// 		if (fd[1] == -1)
// 		{
// 			perror(temp->file);
// 			return false;
// 		}
// 		*out = 1;
// 	}
// 	return (true);
// }

// int	do_pipe(int *fd)
// {
// 	int fd_pipe[2];
// 	pipe(fd_pipe);
// 	fd[1] = fd_pipe[1];
// 	fd[0] = fd_pipe[0];
// 	return (1);
// }

// bool	check_redir_list(t_cmd_list *lst, int *fd)
// {
// 	t_redir	*temp;
// 	int		out;
// 	int pip = 0;

// 	out = 0;
// 	dup2(fd[0], STDIN_FILENO);
// 	temp = lst->redir;
// 	while(temp)
// 	{
// 		if(temp->type == REDIR_INPUT || temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APPEND)
// 		{
// 			if (do_redir(temp, fd, &out) == false);
// 				return (false);
// 		}
// 		temp = temp->next;
// 	}
// 	if (out == 0 && lst->next != NULL)
// 		pip = do_pipe(fd);
// 	if (out == 0 && pip == 0)
// 		fd[1] = dup(fd[3]);
// 	return true;
// }

bool	check_redir_list(t_cmd_list *lst, int *fd)
{
	t_redir *temp = lst->redir;
	int out = 0;
	int pip = 0;

	dup2(fd[0], STDIN_FILENO);
	while(temp)
	{
		if(temp->type == REDIR_INPUT)
		{
			fd[0] = open(temp->file, O_RDONLY);
			if (fd[0] == -1)
			{
				perror(temp->file);
				return false;
			}
			dup2(fd[0], STDIN_FILENO);
		}
		if (temp->type == REDIR_OUTPUT)
		{
			fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd[1] == -1)
			{
				perror(temp->file);
				return false;
			}
			out = 1;
		}
		if (temp->type == REDIR_OUTPUT_APPEND)
		{
			fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND);
			if (fd[1] == -1)
			{
				perror(temp->file);
				return false;
			}
			out = 1;
		}
		temp = temp->next;
	}
	if (out == 0 && lst->next != NULL)
	{
		int fd_pipe[2];
		pipe(fd_pipe);
		fd[1] = fd_pipe[1];
		fd[0] = fd_pipe[0];
		pip = 1;
	}
	if (out == 0 && pip == 0)
		fd[1] = dup(fd[3]);
	return true;
}