
#include "../include/pipe.h"

uint32_t lst_size(t_list *lst)
{
	uint32_t i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return i;
}

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

char	*get_env(char **envp, char *path)
{
	int		i;
	char	*env;

	i = 0;
	while (envp[i])
	{
		env = ft_strnstr(envp[i], path, ft_strlen(path));
		if (env != NULL)
		{
			env = env + 5;
			return (env);
		}
		i++;
	}
	return (NULL);
}

// char *get_env(t_list *envp, char *env)
// {
// 	while (envp)
// 	{
// 		if (strcmp(envp->content, env) == 0)
// 			return (envp->content + strlen(env));
// 		envp = envp->next;
// 	}
// 	return (NULL);
// }

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
	// if (paths == NULL)
		// exit_msg("Malloc in ft_split has failed", NULL, 1);
	// printf("HEY\n");
	// printf("%s\n", paths[0]);
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

	i = lst_size(lst);
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
		printf("%s\n", cmd);
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
	uint32_t CMD_NUMS = list_size(data.cmd_list);

	while (temp)
	{
		// fprintf(stderr, "%p\n", temp->redir);
		cmd = check_redir_list(temp->redir, fd);
		dup2(fd[1], STDOUT_FILENO); 
		close(fd[1]);


		if (cmd == true)
		{
			if (check_builtin(temp->cmd) == true)
				run_builtin(temp, data.env_lst);
			else
			{
				ret = fork();
				if (ret == 0)
				{
					// printf("cmd: %s\n", temp->cmd);
					exec_cmd(temp, data.env_lst);
					// execve(temp->cmd, temp->args, envp);
					exit(1);
				}
			}
		}
		temp = temp->next;
		i++;
	} // for loop

	int status;
	for (int i = 0; i < CMD_NUMS; i++)
	{
		wait(&status);
	}
	// print_env_lst(data.env_lst);
	// printf("%s\n", getcwd(NULL, 0));
	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
}

void temp_cmd(t_cmd_list **lst, char *cmd, char **args);
void temp_cmd_pipe(t_cmd_list **lst, char **arg1, char **arg2);

int main(int argc, char *argv[], char *envp[])
{
	t_data data;
	bool is_running = true;
	data.env_lst = NULL;
	create_env_lst(envp, &data.env_lst);
	// printf("%s\n", getcwd(NULL, 0));

	// cmd_one(&data.cmd_list);
	// cmd_two(&data.cmd_list);
	// cmd_three(&data.cmd_list);
	// cmd_four(&data.cmd_list);
	// cmd_five(&data.cmd_list);
	// cmd_six(&data.cmd_list);
	// cmd_seven(&data.cmd_list);
	// cmd_eight(&data.cmd_list);
	// cmd_nine(&data.cmd_list);
	// cmd_ten(&data.cmd_list);
	// cmd_eleven(&data.cmd_list);
	while (is_running)
	{
		char *line = readline("");
		add_history(line);
		// char *line = "ls";
		if (strcmp(line, "exit") == 0)
			exit(0);
		if (line)
		{
			// char **args = ft_split(line, ' ');
			char **args;
			// if (strchr(line, '|') != NULL)
			// {
			// 	// printf("PIPE\n");
			// 	args = ft_split(line, '|');
			// 	// args = ft_split(args[1], ' ');
			// 	// for (int i = 0; args[i]; i++)
			// 	// 	printf("%s\n", args[i]);

			// 	char **arg1 = ft_split(args[0], ' ');
			// 	char **arg2 = ft_split(args[1], ' ');
			// 	// temp_cmd(&data.cmd_list, arg1[0], arg1);
			// 	// pipex(data);
			// 	// if (arg1[0] && arg2[0])
			// 	// {
			// 	// 	// printf("CHECK\n");
			// 	// 	temp_cmd_pipe(&data.cmd_list, arg1, arg2);
			// 	// 	pipex(data);
			// 	// }
			// 	temp_cmd_pipe(&data.cmd_list, arg1, arg2);
			// 	pipex(data);
			// }
			// else
			// {
			// 	args = ft_split(line, ' ');
			// 	if (args[0]) {
			// 		temp_cmd(&data.cmd_list, args[0], args);
			// 		pipex(data);
			// 	}
			// }
			args = ft_split(line, ' ');
			if (args[0]) {
				temp_cmd(&data.cmd_list, args[0], args);
				pipex(data);
			}

		}
		printf("\n");
		// exit(0);
	}
}
