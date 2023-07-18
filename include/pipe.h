#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include <signal.h>
# include <stdint.h>


typedef enum s_redir_type
{
	REDIR_PIPE = 0,
	REDIR_INPUT = 1,
	REDIR_OUTPUT = 2,
	REDIR_INPUT_APPEND = 3,
	REDIR_OUTPUT_APPEND = 4
} t_redir_type;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_list
{
	char	*cmd;
	char	**args;
	t_redir	*redir;

	struct s_cmd_list	*next;
}	t_cmd_list;


typedef struct s_data
{
	t_cmd_list	*cmd_list;
}	t_data;

void str_cpy(char *dest, char *src);

uint32_t list_size(t_cmd_list *list);

t_cmd_list *create_cmd_list(char *cmd, char **args);

void	add_back(t_cmd_list **list, t_cmd_list *new);

void redir_add_back(t_cmd_list **head, t_redir *new);

t_redir	*new_redir_node();

void check_redir(t_redir *redir, int fd[]);

void print_args(t_cmd_list *lst);

void print_redir_list(t_redir *lst);

void check_redir_list(t_redir *lst, int *fd);

#endif