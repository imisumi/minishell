

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
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>


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

#endif