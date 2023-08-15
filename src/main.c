/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:12:16 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/15 14:27:32 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"

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

char	**env_paths(char **envp)
{
	int		i;
	char	*env;
	char	*temp;
	char	**paths;

	// paths[0] = NULL;
	env = get_env(envp, "PATH=");
	// printf("%s\n", env);
	if (env == NULL)
		return (NULL);
	paths = ft_split(env, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = temp;
		// printf("PATH: %s\n", paths[i]);
		i++;
	}
	// exit(0);
	return (paths);
}

char	**lst_to_arr(t_list *lst)
{
	int		i;
	char	**envp;

	i = ft_lstsize(lst);
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (lst)
	{
		envp[i] = lst->content;
		i++;
		lst = lst->next;
	}
	envp[i] = NULL;
	return envp;
}

char	*find_path(char *cmd, char **paths)
{
	int	i;
	char *temp;

	i = 0;
	if (paths == NULL)
		return (cmd);
	while (paths[i])
	{
		// temp = ft_strjoin("/", cmd);
		temp = ft_strjoin(paths[i], cmd);
		free(paths[i]);
		paths[i] = temp;
		// printf("%s\n", temp);
		// printf("%s\n", paths[i]);
		// printf("\n");
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

	//TODO: 
	//!
	//?

	envp = lst_to_arr(env_lst);
	paths = env_paths(envp);
	if (ft_strchr(lst->cmd, '/') != NULL)
	{
		execve(lst->cmd, lst->args, envp);
		perror(lst->cmd);
		exit(1);
	}
	else
	{
		cmd = find_path(lst->cmd, paths);
		// printf("%s\n", cmd);
		execve(cmd, lst->args, envp);
		// perror(cmd);
		// _Exit(1);
		_exit(1);
		exit(1);
	}
	exit(1);
}

void	pipex(t_data data)
{
	bool cmd = true;

	t_cmd_list *temp = data.cmd_list;

	//! [0] = fd_in
	//! [1] = fd_out
	//! [2] = temp_in == STDIN_FILENO
	//! [3] = temp_out == STDOUT_FILENO
	int fd[4];
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);

	int ret;
	int i = 0;
	uint32_t CMD_NUMS = cmd_list_size(data.cmd_list);
	if (CMD_NUMS == 1 && strcmp(temp->cmd, "exit") == 0)
	{
		printf("exiting\n");
		exit(0);
	}
	// printf("%d\n", CMD_NUMS);
	while (temp)
	{
		cmd = check_redir_list(temp, fd);
		dup2(fd[1], STDOUT_FILENO); 
		close(fd[1]);
		if (cmd == true)
		{
			if (check_builtin(temp->cmd) == true)
			{
				run_builtin(data);
			}
			else
			{
				ret = fork();
				if (ret == 0)
				{
					// printf("cmd: %s\n", temp->cmd);
					exec_cmd(temp, data.env_lst);
					// perror("");
					// execve(temp->cmd, temp->args, envp);
					exit(1);
				}
			}
		}
		temp = temp->next;
		i++;
	} // while loop

	int status;
	for (int i = 0; i < CMD_NUMS; i++)
	{
		wait(&status);
	}
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
}

void temp_cmd(t_cmd_list **lst, char *cmd, char **args);
void temp_cmd_pipe(t_cmd_list **lst, char **arg1, char **arg2);
// t_list	*init_env_lst(t_data d, char **envp);
void	init_env_lst(t_data *d, char **envp);

t_utils	init_utils()
{
	t_utils	utils;
	char	*temp;

	temp = getcwd(NULL, 0);
	utils.local_dir = ft_strjoin(temp, "/.env.ms");
	free(temp);
	return utils;
}

void	print_handle(void)
{
	char *start = "\033[31;1mMS \033[1;38;5;206m➜ \033[1;36m";
	char *end = "\033[1;34m$\033[0m";
	char *temp;
	char *dir;
	char *ms;

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
	// char * temp = getcwd(NULL, 0);
	// local_dir = ft_strjoin(temp, "/.env.ms");
	// data.utils.local_dir = ft_strjoin(temp, "/.env.ms");
	// free(temp);
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
				args = ft_split(line, ' ');
				if (args[0]) {
					temp_cmd(&data.cmd_list, args[0], args);
					pipex(data);
				}
			}
			free(line);
		}
		printf("\n");
	}
}
