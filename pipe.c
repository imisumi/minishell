
#include "pipe.h"

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

void str_cpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

uint32_t list_size(t_cmd_list *list)
{
	uint32_t size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

t_cmd_list *create_cmd_list(char *cmd, char **args)
{
	//print args
	// for (int i = 0; args[i]; i++)
	// 	printf("args[%d]: %s\n", i, args[i]);

	t_cmd_list *cmd_list;

	cmd_list = calloc(sizeof(t_cmd_list), 1);
	cmd_list->cmd = calloc(sizeof(char), strlen(cmd) + 1);
	str_cpy(cmd_list->cmd, cmd);

	cmd_list->args = calloc(sizeof(char *), 10);
	for (int i = 0; args[i]; i++)
	{
		cmd_list->args[i] = calloc(sizeof(char), 10);
		// strcpy(cmd_list->args[i], args[i]);
		str_cpy(cmd_list->args[i], args[i]);
		// printf("check\n");
	}
	cmd_list->next = NULL;
	cmd_list->redir = NULL;
	return (cmd_list);
}

void	add_back(t_cmd_list **list, t_cmd_list *new)
{
	t_cmd_list *temp;

	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	// return (list);
}

void redit_add_back(t_cmd_list **head, t_redir **new_redir)
{
	if (*head == NULL)
    {
        (*head)->redir = *new_redir;
    }
    // if (*head == NULL)
    // {
    //     (*head)->redir = *new_redir;
    // }
    // else
    // {
    //     t_redir *current = (*head)->redir;
    //     while (current->next != NULL)
    //     {
    //         current = current->next;
    //     }
    //     current->next = *new_redir;
    // }
}

void redir_add_back(t_cmd_list **head, t_redir *new)
{
	// if (*head == NULL)
	// {
	// 	(*head) = new;
	// }
	if ((*head)->redir == NULL)
		(*head)->redir = new;
	else
	{
		t_redir *current = (*head)->redir;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;
	}
	// else
	// {
	// 	t_redir *current = (*head);
	// 	while (current->next != NULL)
	// 	{
	// 		current = current->next;
	// 	}
	// 	current->next = new;
	// }
}

t_redir	*new_redir_node()
{
	t_redir *new;

	new = calloc(sizeof(t_redir), 1);
	if (new == NULL)
		exit(1);
	new->file = calloc(sizeof(char), 64);
	new->type = REDIR_PIPE;
	new->next = NULL;
	return (new);
}

int main(void)
{
	t_data data;

	data.cmd_list = create_cmd_list("/usr/bin/grep", (char *[]){"grep", "N", NULL});

	t_redir *new = new_redir_node();
	str_cpy(new->file, "Makefile");
	new->type = REDIR_INPUT;

	redir_add_back(&data.cmd_list, new);

	new = new_redir_node();
	str_cpy(new->file, "out");
	new->type = REDIR_OUTPUT;

	redir_add_back(&data.cmd_list, new);

	// new_redir_node(&(data.cmd_list));
	t_cmd_list *temp = data.cmd_list;
	t_redir *tmp = data.cmd_list->redir;
	printf("type: %u\n", tmp->type);
	printf("file: %s\n", tmp->file);
	printf("next: %p\n", tmp->next);
	tmp = tmp->next;
	printf("type: %u\n", tmp->type);
	printf("file: %s\n", tmp->file);
	printf("next: %p\n", tmp->next);
	return 0;
	int i = 0;
	// while (temp)
	// {
	// 	printf("path: %s\n", temp->cmd);
	// 	printf("args: ");
	// 	i = 0;
	// 	while (temp->args[i])
	// 	{
	// 		printf("%s ", temp->args[i]);
	// 		i++;
	// 	}
	// 	printf("\n\n");
	// 	if (temp->next == NULL)
	// 		break ;
	// 	temp = temp->next;
	// }
	// temp = data.cmd_list;


	// t_cmd_list *temp = data.cmd_list;
	// if (temp == NULL)
	// 	printf("NULL\n");
	// else
	// {
	// 	printf("type: %u\n", temp->redir->type);
	// 	printf("file: %s\n", temp->redir->file);
	// }
	// temp = temp->next;
	// if (temp == NULL)
	// 	printf("NULL\n");
	// else
	// {
	// 	printf("type2: %u\n", temp->redir->type);
	// 	printf("file2: %s\n", temp->redir->file);
	// }
	// printf("check\n");



	// temp = data.cmd_list;

	//! [0] = fd_in
	//! [1] = fd_out
	//! [2] = temp_in
	//! [3] = temp_out
	int fd[4];
	fd[2] = dup(STDIN_FILENO);
	fd[3] = dup(STDOUT_FILENO);
	char *infile = "Makefile";
	// char *outfile = NULL;
	char *outfile = "out";
	if (infile)
		fd[0] = open(infile, O_RDONLY);
	else
		fd[0] = dup(fd[2]);
	
	int ret;
	i = 0;
	uint32_t CMD_NUMS = list_size(data.cmd_list);
	// printf("CMD_NUMS: %d\n", CMD_NUMS);
	// exit(1);
	while (temp)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		if (i == CMD_NUMS - 1)
		{
			check_redir(temp->redir, fd);
			// fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			// if (outfile)
			// 	fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			// else
			// 	fd[1] = dup(fd[3]);
		}
		else
		{
			int fd_pipe[2];
			pipe(fd_pipe);
			fd[1] = fd_pipe[1];
			fd[0] = fd_pipe[0];
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ret = fork();
		if (ret == 0)
		{
			execve(temp->cmd, temp->args, NULL);
			exit(1);
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