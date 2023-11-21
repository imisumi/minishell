/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:47:43 by rhorbach          #+#    #+#             */
/*   Updated: 2023/11/21 16:23:35 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "cmd_lst.h"

void	catch_child_exit(int cmd_nums, pid_t *child_pids)
{
	int		i;
	int		status;

	i = 0;
	while (i < cmd_nums)
	{
		if (child_pids[i] != -1)
		{
			if (waitpid(child_pids[i], &status, 0) == -1)
			{
				if (get_exit_code() != NOT_RECOVERABLE)
					set_exit_code(CONTROL_C_TERMINATED);
				return ;
			}
			else if (WIFEXITED(status))
				set_exit_code(WEXITSTATUS(status));
		}
		i++;
	}
}

void	init_fds(t_data *data)
{
	data->utils.fd[0] = dup(STDIN_FILENO);
	data->utils.fd[1] = dup(STDOUT_FILENO);
	data->utils.fd[2] = dup(STDIN_FILENO);
	data->utils.fd[3] = dup(STDOUT_FILENO);
}

void	do_child_process(t_data *data, t_cmd_list *temp, bool redir)
{
	free_data_utils(data);
	if (data->utils.fd[0] >= 0)
		close(data->utils.fd[0]);
	print_open_fd();
	if (redir == false)
	{
		free_data_cmd(data);
		exit(1);
	}
	if (check_builtin(temp->args[0]) == true)
		exit(run_pipe_builtin(data, temp));
	else
		exit(exec_cmd(data, temp));
}

void	pipex_2(t_data *data, t_cmd_list *temp)
{
	bool		redir;
	int			i;
	pid_t		ret;

	i = 0;
	while (temp && ++i)
	{
		redir = check_redir_list(data, temp);
		dup2(data->utils.fd[1], STDOUT_FILENO);
		close(data->utils.fd[1]);
		if (temp->args[0] != NULL)
		{
			enable_sigint_pipe();
			ret = fork();
			if (ret == CHILD)
				do_child_process(data, temp, redir);
			else if (ret > 0)
				data->utils.child_pids[i - 1] = ret;
			else
				perror("fork");
		}
		else
			data->utils.child_pids[i - 1] = -1;
		temp = temp->next;
	}
}

//! [0] = fd_in
//! [1] = fd_out
//! [2] = temp_in == STDIN_FILENO
//! [3] = temp_out == STDOUT_FILENO
t_error	pipex(t_data *data)
{
	int			cmd_nums;
	t_cmd_list	*temp;

	temp = data->cmd_list;
	init_fds(data);
	cmd_nums = cmd_lstsize(data->cmd_list);
	if (cmd_nums == 1 && check_builtin(temp->args[0]) == true)
		return (run_single_builtin(data, temp), OK);
	data->utils.child_pids = malloc(sizeof(pid_t) * cmd_nums);
	if (!data->utils.child_pids)
		return (set_error(E_SYS));
	pipex_2(data, temp);
	dup2(data->utils.fd[2], STDIN_FILENO);
	dup2(data->utils.fd[3], STDOUT_FILENO);
	close(data->utils.fd[2]);
	close(data->utils.fd[3]);
	if (data->utils.fd[0] >= 0)
		close(data->utils.fd[0]);
	catch_child_exit(cmd_nums, data->utils.child_pids);
	enable_sigint();
	free(data->utils.child_pids);
	return (OK);
}
