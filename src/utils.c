
#include "../include/pipe.h"




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

void print_args(t_cmd_list *lst)
{
	int i;
	t_cmd_list *temp = lst;
	while(temp)
	{
		printf("%s\n", temp->cmd);
		i = 0;
		while (temp->args[i])
		{
			printf("%s ", temp->args[i]);
			i++;
		}
		temp = temp->next;
        printf("\n");
	}
	printf("\n");
	// printf("check\n");
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

void check_redir_list(t_redir *lst, int *fd)
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
            // printf("temp->file: %s\n", temp->file);
            fd[0] = open(temp->file, O_RDONLY);
			// print perror
			perror(temp->file);
			printf("fd[0]: %d\n", fd[0]);
            dup2(fd[0], STDIN_FILENO);
            in = 1;
        }
        if (temp->type == REDIR_OUTPUT)
        {
            // printf("temp->file: %s\n", temp->file);

            fd[1] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            out = 1;
        }
		if (temp->type == REDIR_OUTPUT_APPEND)
        {
            // printf("temp->file: %s\n", temp->file);

            fd[1] = open(temp->file, O_WRONLY | O_APPEND);
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
    // if (in == 0)
    //     fd[0] = dup(fd[2]);
    // if (out == 0)
        // fd[1] = dup(fd[3]);
    // dup2(fd[0], STDIN_FILENO);
    // close(fd[0]);
    if (out == 0 && pip == 0)
        fd[1] = dup(fd[3]);
    // else
    //     dup2(fd[1], STDOUT_FILENO);
	// if ()

    return ;
}

bool	check_builtin(char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		return (true);
	if (strcmp(cmd, "cd") == 0)
		return (true);
	if (strcmp(cmd, "pwd") == 0)
		return (true);
	if (strcmp(cmd, "export") == 0)
		return (true);
	if (strcmp(cmd, "unset") == 0)
		return (true);
	if (strcmp(cmd, "env") == 0)
		return (true);
	if (strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool str_cmp(char *s1, char *s2)
{
	int	i;

	if(!s1 || !s2)
		return (false);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

void run_builtin(t_cmd_list *lst)
{
	char	*cwd;
	// printf("%s\n", lst->cmd);
	if (strcmp(lst->cmd, "pwd") == 0)
	{
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
		free(cwd);
	}
	if (strcmp(lst->cmd, "echo") == 0)
	{
		if (str_cmp(lst->args[1], "-n") == true)
		{
			if (lst->args[2] == NULL)
				return ;
			printf("%s", lst->args[2]);
		}
		else
		{
			if (lst->args[1] == NULL)
				return ;
			printf("%s\n", lst->args[1]);
		}
	}
}


//! redir utils

void add_input_node(t_cmd_list **lst, char *file)
{
	t_redir *new = new_redir_node();
	str_cpy(new->file, file);
	new->type = REDIR_INPUT;
	redir_add_back(lst, new);
}

void add_output_node(t_cmd_list **lst, char *file)
{
	t_redir *new = new_redir_node();
	str_cpy(new->file, file);
	new->type = REDIR_OUTPUT;
	redir_add_back(lst, new);
}

void add_pipe_node(t_cmd_list **lst)
{
	t_redir *new = new_redir_node();
	new->type = REDIR_PIPE;
	new->file = NULL;
	redir_add_back(lst, new);
}

void add_append_output_node(t_cmd_list **lst, char *file)
{
	t_redir *new = new_redir_node();
	str_cpy(new->file, file);
	new->type = REDIR_OUTPUT_APPEND;
	redir_add_back(lst, new);
}