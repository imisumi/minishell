/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi <imisumi@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 14:31:38 by imisumi       #+#    #+#                 */
/*   Updated: 2023/11/16 16:44:52 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

bool	check_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

static void	run_single_builtin_2(t_data *data, t_cmd_list *lst)
{
	char	*cwd;

	if (ft_strcmp(lst->args[0], "pwd") == 0)
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		set_exit_code(0);
	}
	if (ft_strcmp(lst->args[0], "echo") == 0)
		set_exit_code(builtin_echo(lst));
	if (ft_strcmp(lst->args[0], "env") == 0)
		set_exit_code(print_env_lst(data->env_lst));
	dup2(data->utils.fd[2], STDIN_FILENO);
	dup2(data->utils.fd[3], STDOUT_FILENO);
	close(data->utils.fd[2]);
	close(data->utils.fd[3]);
	if (data->utils.fd[0] >= 0)
		close(data->utils.fd[0]);
}

void	run_single_builtin(t_data *data, t_cmd_list *lst)
{
	int		exit_code;

	if (!check_redir_list(data, lst))
		return ;
	dup2(data->utils.fd[1], STDOUT_FILENO);
	close(data->utils.fd[1]);
	if (ft_strcmp(lst->args[0], "unset") == 0)
		set_exit_code(builtin_unset(data, lst));
	if (ft_strcmp(lst->args[0], "export") == 0)
		set_exit_code(builtin_export(data, lst));
	if (ft_strcmp(lst->args[0], "cd") == 0)
		set_exit_code(builtin_cd(data, lst));
	if (ft_strcmp(lst->args[0], "exit") == 0)
	{
		exit_code = builtin_exit(lst, true);
		free(data->utils.local_dir);
		free_data_cmd(data);
		rl_clear_history();
		exit(exit_code);
	}
	run_single_builtin_2(data, lst);
}

int	run_pipe_builtin(t_data *d, t_cmd_list *lst)
{
	char	*cwd;

	if (ft_strcmp(lst->args[0], "unset") == 0)
		exit(0);
	if (ft_strcmp(lst->args[0], "export") == 0)
		exit(builtin_export(d, lst));
	if (ft_strcmp(lst->args[0], "cd") == 0)
		exit(builtin_cd(d, lst));
	if (ft_strcmp(lst->args[0], "exit") == 0)
		exit(builtin_exit(lst, false));
	if (ft_strcmp(lst->args[0], "pwd") == 0)
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		exit(0);
	}
	if (ft_strcmp(lst->args[0], "echo") == 0)
		exit(builtin_echo(lst));
	if (ft_strcmp(lst->args[0], "env") == 0)
		exit(print_env_lst(d->env_lst));
	return (0);
}
