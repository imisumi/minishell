/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi <imisumi@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 17:47:43 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/16 16:33:42 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	exec_error_msg(char	*cmd, char **paths)
{
	int		exit_code;

	exit_code = 127;
	if (access(cmd, F_OK) == 0)
		exit_code = fd_put_err(cmd, " :Is a directory\n", 126);
	else if (paths == NULL)
		fd_put_err(cmd, " :No such file or directory\n", 127);
	else if (ft_strchr(cmd, '/') != NULL)
		fd_put_err(cmd, " :No such file or directory\n", 127);
	else
		fd_put_err(cmd, " :command not found\n", 127);
	free_2d_array(paths);
	return (free(cmd), exit_code);
}

bool	valid_command(t_data *data, char **paths, char **envp, char *cmd)
{
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
	{
		fd_put_err(cmd, " :Permission denied\n", 126);
		free_child_data(data, envp, paths);
		return (126);
	}
	return (true);
}

//! if absolute path, check if file exists
//! else loop true env paths
int	exec_cmd(t_data *data, t_cmd_list *lst)
{
	char	**envp;
	char	**paths;
	char	*cmd;
	char	*arg;

	arg = ft_strdup(lst->args[0]);
	envp = env_list_to_array(data->env_lst);
	paths = env_paths(data->env_lst);
	if (ft_strchr(arg, '/') != NULL || paths == NULL)
	{
		if (valid_command(data, paths, envp, arg) == false)
			return (126);
		execve(arg, lst->args, envp);
	}
	else
	{
		cmd = find_path(arg, paths);
		if (valid_command(data, paths, envp, cmd) == false)
			return (126);
		execve(cmd, lst->args, envp);
	}
	free_2d_array(envp);
	free_data_cmd(data);
	return (exec_error_msg(arg, paths));
}
