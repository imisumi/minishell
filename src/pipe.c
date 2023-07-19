
#include "../include/pipe.h"


int main(void)
{
	t_data data;


	// cmd_one(&data.cmd_list);
	// cmd_two(&data.cmd_list);
	// cmd_three(&data.cmd_list);
	// cmd_four(&data.cmd_list);
	// cmd_five(&data.cmd_list);
	// cmd_six(&data.cmd_list);
	cmd_seven(&data.cmd_list);

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
				execve(temp->cmd, temp->args, NULL);
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



// int main(void)
// {
// 	t_data data;

// 	// data.cmd_list = create_cmd_list("/bin/cat", (char *[]){"cat", NULL});
// 	// data.cmd_list = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
// 	data.cmd_list = create_cmd_list("/usr/bin/grep", (char *[]){"grep", "ru", NULL});

// 	t_redir *new = new_redir_node();
// 	str_cpy(new->file, "out");
// 	new->type = REDIR_OUTPUT;

// 	redir_add_back(&data.cmd_list, new);

// 	new = new_redir_node();
// 	str_cpy(new->file, "Makefile");
// 	new->type = REDIR_INPUT;

// 	redir_add_back(&data.cmd_list, new);

	

// 	// print_redir_list(data.cmd_list->redir);
// 	print_args(data.cmd_list);

// 	return 0;
// 	int i = 0;

// 	t_cmd_list *temp = data.cmd_list;

// 	//! [0] = fd_in
// 	//! [1] = fd_out
// 	//! [2] = temp_in
// 	//! [3] = temp_out
// 	int fd[4];
// 	fd[2] = dup(STDIN_FILENO);
// 	fd[3] = dup(STDOUT_FILENO);


// 	// char *infile = "Makefile";
// 	// // char *outfile = NULL;
// 	// char *outfile = "out";
// 	// if (infile)
// 	// 	fd[0] = open(infile, O_RDONLY);
// 	// else
// 	// 	fd[0] = dup(fd[2]);
	
// 	int ret;
// 	i = 0;
// 	uint32_t CMD_NUMS = list_size(data.cmd_list);
// 	// printf("CMD_NUMS: %d\n", CMD_NUMS);
// 	// exit(1);
// 	while (temp)
// 	{
// 		check_redir_list(temp->redir, fd);


// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		ret = fork();
// 		if (ret == 0)
// 		{
// 			// char *cmd[] = {"ls", "-la", NULL};
// 			// printf("%s\n", temp->cmd);
// 			// print_args(temp);
// 			execve(temp->cmd, temp->args, NULL);
// 			// execve("/bin/ls", cmd, NULL);
// 			exit(1);
// 		}
// 		temp = temp->next;
// 		i++;
// 	} // for loop

// 	int status;
// 	for (int i = 0; i < CMD_NUMS; i++)
// 	{
// 		wait(&status);
// 	}

// 	dup2(fd[2], STDIN_FILENO);
// 	dup2(fd[3], STDOUT_FILENO);
// 	close(fd[2]);
// 	close(fd[3]);
// }

// int main(void)
// {
// 	char *cmd[][10] = {
// 		{"ls", "-la", NULL},
// 		{"grep", "10", NULL},
// 		{"grep", "1", NULL}
// 	};
// 	char *path[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/grep", NULL};
// 	int temp_in = dup(STDIN_FILENO);
// 	int temp_out = dup(STDOUT_FILENO);
// 	char *infile = "Makefile";
// 	// char *outfile = NULL;
// 	char *outfile = "out";
// 	int fd_in;
// 	if (infile)
// 		fd_in = open(infile, O_RDONLY);
// 	else
// 		fd_in = dup(temp_in);
	
// 	int fd_out;
// 	int ret;
// 	for (int i = 0; i < CMD_NUMS; i++)
// 	{
// 		dup2(fd_in, STDIN_FILENO);
// 		close(fd_in);

// 		if (i == CMD_NUMS - 1)
// 		{
// 			if (outfile)
// 				fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else
// 				fd_out = dup(temp_out);
// 		}
// 		else
// 		{
// 			int fd_pipe[2];
// 			pipe(fd_pipe);
// 			fd_out = fd_pipe[1];
// 			fd_in = fd_pipe[0];
// 		}
// 		dup2(fd_out, STDOUT_FILENO);
// 		close(fd_out);
// 		ret = fork();
// 		if (ret == 0)
// 		{
// 			execve(path[i], cmd[i], NULL);
// 			exit(1);
// 		}
// 	} // for loop

// 	int status;
// 	for (int i = 0; i < CMD_NUMS; i++)
// 	{
// 		wait(&status);
// 	}

// 	dup2(temp_in, STDIN_FILENO);
// 	dup2(temp_out, STDOUT_FILENO);
// 	close(temp_in);
// 	close(temp_out);
// }