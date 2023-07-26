
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

char	*get_env_path(char **envp)
{
	int		i;
	char	*env;

	i = 0;
	while (envp[i])
	{
		env = ft_strnstr(envp[i], "PATH=", 5);
		if (env != NULL)
		{
			env = env + 5;
			return (env);
		}
		i++;
	}
	return (NULL);
}

char	**env_paths(char **envp)
{
	int		i;
	char	*env;
	char	*temp;
	char	**paths;

	// paths[0] = NULL;
	env = get_env_path(envp);
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
		if (temp == NULL)
		{
			free_2d_arr(paths);
			// exit_msg("Malloc in ft_strjoin has failed", NULL, 1);
		}
		free(paths[i]);
		paths[i] = temp;
		i++;
	}
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
		temp = ft_strjoin(paths[i], cmd);
		free(paths[i]);
		paths[i] = temp;
		// printf("%s\n", temp);
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
		execve(lst->cmd, lst->args, envp);
		perror(lst->cmd);
		exit(1);
	}
	else
	{
		cmd = find_path(lst->cmd, paths);
		printf("%s\n", cmd);
		execve(cmd, lst->args, envp);
		perror(cmd);
		exit(1);
	}
	exit(1);
}

int main(int argc, char *argv[], char *envp[])
{
	t_data data;
	t_list	*env_lst = NULL;
	create_env_lst(envp, &env_lst);
	// printf("%s\n", env_lst->content);
	// add_env(&env_lst, "z=hello");
	// add_env(&env_lst, "PATH=noob");
	// add_env(&env_lst, "ff=boo");
	// add_env(&env_lst, "asd");

	// unset_env(&env_lst, "PATH");
	unset_env(&env_lst, "PATH");
	// unset_env(&env_lst, "z");
	// unset_env(&env_lst, "hey");


	// print_env_lst(env_lst);
	// fill_env_file(env_lst);
	// return 0;


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
	cmd_eleven(&data.cmd_list);


	int i = 0;
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
	i = 0;
	uint32_t CMD_NUMS = list_size(data.cmd_list);

	// exec_cmd(temp, env_lst);
	// return 0;

	while (temp)
	{
		// fprintf(stderr, "%p\n", temp->redir);
		cmd = check_redir_list(temp->redir, fd);
		if (temp->next)
		{
			
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);


		if (cmd == true)
		{
			if (check_builtin(temp->cmd) == true)
				run_builtin(temp);
			else
			{
				ret = fork();
				if (ret == 0)
				{
					// printf("cmd: %s\n", temp->cmd);
					exec_cmd(temp, env_lst);
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

	dup2(fd[2], STDIN_FILENO);
	dup2(fd[3], STDOUT_FILENO);
	close(fd[2]);
	close(fd[3]);
}
