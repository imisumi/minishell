/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:12:16 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/20 19:57:20 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"

t_exit_code	g_exit_code;

void	free_2d_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

char	*find_path(char *cmd, char **paths)
{
	int		i;
	char	*temp;

	i = 0;
	if (paths == NULL)
		return (cmd);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], cmd);
		free(paths[i]);
		paths[i] = temp;
		if (access(paths[i], F_OK | X_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (cmd);
}

void	exec_cmd(t_cmd_list *lst, t_list *env_lst)
{
	char	**envp;
	char	**paths;
	char	*cmd;

	envp = lst_to_arr(env_lst);
	paths = env_paths(envp);
	if (ft_strchr(lst->cmd, '/') != NULL)
	{
		if (access(lst->cmd, F_OK) == 0)
		{
			if (access(lst->cmd, X_OK) != 0)
				exit (126);
		}
		execve(lst->cmd, lst->args, envp);
	}
	else
	{
		//! looping env paths
		cmd = find_path(lst->cmd, paths);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
			exit (126);
		execve(cmd, lst->args, envp);
	}
	exit(127);
}

void	child_exit(int cmd_nums, pid_t *child_pids)
{
	int		i;
	int		status;
	int		exit_status;
	pid_t	child;

	i = 0;
	while (i < cmd_nums)
	{
		child = waitpid(child_pids[i], &status, 0);
		// if (child == -1) {
			// perror("waitpid");
			// return EXIT_FAILURE;
		// }
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			g_exit_code = exit_status;
			// printf("Child process %d exited with status: %d\n", child, exit_status);
		}
		i++;
	}
}

//! [0] = fd_in
//! [1] = fd_out
//! [2] = temp_in == STDIN_FILENO
//! [3] = temp_out == STDOUT_FILENO
void	pipex(t_data data)
{
	bool		cmd;
	int			cmd_nums;
	int			i;
	int			fd[4];
	t_cmd_list	*temp;
	pid_t		ret;

	cmd = true;
	temp = data.cmd_list;
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	i = 0;
	cmd_nums = cmd_list_size(data.cmd_list);
	if (cmd_nums == 1 && strcmp(temp->cmd, "exit") == 0)
		exit(0);
	pid_t *child_pids = malloc(sizeof(pid_t) * cmd_nums);
	while (temp)
	{
		cmd = check_redir_list(temp, fd);
		dup2(fd[1], STDOUT_FILENO); 
		close(fd[1]);
		if (cmd == true)
		{
			if (check_builtin(temp->cmd) == true)
			{
				// printf("builtin\n");
				run_builtin(data, temp);
			}
			else
			{
				// printf("fork\n");
				ret = fork();
				if (ret == 0)
					exec_cmd(temp, data.env_lst);
			}
		}
		temp = temp->next;
		i++;
	} // while loop

	child_exit(cmd_nums, child_pids);
	free(child_pids);
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
}


t_utils	init_utils()
{
	t_utils	utils;
	char	*temp;

	temp = getcwd(NULL, 0);
	utils.local_dir = ft_strjoin(temp, "/.env.ms");
	free(temp);
	return (utils);
}

void	print_handle(void)
{
	char	*start;
	char	*end;
	char	*temp;
	char	*dir;
	char	*ms;

	start = "\033[31;1mMS \033[1;38;5;206m➜ \033[1;36m";
	end = "\033[1;34m$\033[0m";
	temp = getcwd(NULL, 0);
	dir = ft_strrchr(temp, '/') + 1;
	free(temp);
	temp = ft_strjoin(start, dir);
	ms = ft_strjoin(temp, end);
	free(temp);
	printf("%s", ms);
	free(ms);
}

int main(int argc, char *argv[], char *envp[])
{
	t_data data;
	bool is_running = true;
	data.env_lst = NULL;
	data.utils = init_utils();
	init_env_lst(&data, envp);
	add_env(data, "OLDPWD=");

	while (is_running)
	{
		print_handle();
		char *line = readline(" ");

		add_history(line);

		if (line)
		{
			char **args;
			if (strchr(line, '|') != NULL)
			{
				args = ft_split(line, '|');

				char **arg1 = ft_split(args[0], ' ');
				char **arg2 = ft_split(args[1], ' ');
				temp_cmd_pipe(&data.cmd_list, arg1, arg2);
				pipex(data);
			}
			else
			{
				// printf("no pipe\n");
				args = ft_split(line, ' ');
				if (args[0]) {
					temp_cmd(&data.cmd_list, args[0], args);
					pipex(data);
				}
			}
			free(line);
		}
		printf("\n");
		printf("exit code = %d\n\n", g_exit_code);
	}
}
