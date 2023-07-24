
#include "../include/pipe.h"



int main(int argc, char *argv[], char *envp[])
{
	t_data data;
	t_list	*env_lst = NULL;
	create_env_lst(envp, &env_lst);
	// printf("%s\n", env_lst->content);
	add_env(&env_lst, "z=hello");
	add_env(&env_lst, "PATH=noob");
	add_env(&env_lst, "ff=boo");
	// add_env(&env_lst, "asd");

	// unset_env(&env_lst, "PATH");
	unset_env(&env_lst, "PATH");
	// unset_env(&env_lst, "z");
	// unset_env(&env_lst, "hey");


	// print_env_lst(env_lst);
	fill_env_file(env_lst);
	return 0;


	// cmd_one(&data.cmd_list);
	// cmd_two(&data.cmd_list);
	// cmd_three(&data.cmd_list);
	// cmd_four(&data.cmd_list);
	// cmd_five(&data.cmd_list);
	// cmd_six(&data.cmd_list);
	// cmd_seven(&data.cmd_list);
	// cmd_eight(&data.cmd_list);
	cmd_nine(&data.cmd_list);


	int i = 0;

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
	// printf("CMD_NUMS: %d\n", CMD_NUMS);
	// exit(1);
	while (temp)
	{
		// fprintf(stderr, "%p\n", temp->redir);
		check_redir_list(temp->redir, fd);

		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		if (check_builtin(temp->cmd) == true)
		{
			run_builtin(temp);
		}
		else
		{
			ret = fork();
			if (ret == 0)
			{
				// printf("cmd: %s\n", temp->cmd);
				execve(temp->cmd, temp->args, envp);
				exit(1);
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
