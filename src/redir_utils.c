#include "../include/pipe.h"

void redir_add_back(t_cmd_list **head, t_redir *new)
{
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

void print_redir_list(t_redir *lst)
{
	t_redir	*temp;

	temp = lst;
	while (temp)
	{
		printf("type: %u\n", temp->type);
		printf("file: %s\n", temp->file);
		printf("next: %p\n", temp->next);
		printf("\n");
		temp = temp->next;
	}
}

bool check_redir_list(t_redir *lst, int *fd)
{
    t_redir *temp = lst;

	int in = 0;
	int out = 0;
	int pip = 0;
	dup2(fd[0], STDIN_FILENO);
	// fd[0] = dup(fd[2]);
	while(temp)
	{
		if(temp->type == REDIR_INPUT)
		{
			fd[0] = open(temp->file, O_RDONLY);
			if (fd[0] == -1)
			{
				perror(temp->file);
				return false;
			}
			dup2(fd[0], STDIN_FILENO);
		}
		if (temp->type == REDIR_OUTPUT)
		{
			fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd[1] == -1)
			{
				perror(temp->file);
				return false;
			}
			out = 1;
		}
		if (temp->type == REDIR_OUTPUT_APPEND)
		{
			fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND);
			if (fd[1] == -1)
			{
				perror(temp->file);
				return false;
			}
			out = 1;
		}
		if (temp->type == REDIR_PIPE && out == 0)
		{
			int fd_pipe[2];
			pipe(fd_pipe);
			fd[1] = fd_pipe[1];
			fd[0] = fd_pipe[0];
			pip = 1;
		}
		temp = temp->next;
	}
	if (out == 0 && pip == 0)
		fd[1] = dup(fd[3]);
	return true;
}