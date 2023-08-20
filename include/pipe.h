#ifndef PIPE_H
# define PIPE_H

# include "struct.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
// #include <readline/readline.h>

# include <signal.h>
# include <stdint.h>

#include "../lib/libft/includes/libft.h"

# include "struct.h"


# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BROWN "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GRAY "\033[0;37m"
# define DARK_GRAY "\033[1;30m"
# define LIGHT_RED "\033[1;31m"
# define LIGHT_GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define LIGHT_BLUE "\033[1;34m"
# define LIGHT_PURPLE "\033[1;35m"
# define LIGHT_CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
// # define PINK "\033[38;5;206m"
# define PINK "\033[1;38;5;206m"
# define PINK2 "\033[1;35m"
# define RESET "\033[0m"

# define COL1 "\033[30;1m"
# define COL2 "\033[31;1m"
# define COL3 "\033[32;1m"
# define COL4 "\033[33;1m"
# define COL5 "\033[34;1m"
# define COL6 "\033[35;1m"
# define COL7 "\033[36;1m"
# define COL8 "\033[37;1m"

char	**env_paths(char **envp);
void	temp_cmd(t_cmd_list **lst, char *cmd, char **args);
void	temp_cmd_pipe(t_cmd_list **lst, char **arg1, char **arg2);
void	init_env_lst(t_data *d, char **envp);



int cmd_list_size(t_cmd_list *list);

t_cmd_list *create_cmd_list(char *cmd, char **args);

void	cmd_list_add_back(t_cmd_list **list, t_cmd_list *new);

void redir_add_back(t_cmd_list **head, t_redir *new);

t_redir	*redir_new_node();

void check_redir(t_redir *redir, int fd[]);

void print_args(t_cmd_list *lst);

void print_redir_list(t_redir *lst);

// bool check_redir_list(t_redir *lst, int *fd);
bool check_redir_list(t_cmd_list *lst, int *fd);




void cmd_one(t_cmd_list **l);
void cmd_two(t_cmd_list **l);
void cmd_three(t_cmd_list **l);
void cmd_four(t_cmd_list **l);
void cmd_five(t_cmd_list **l);
void cmd_six(t_cmd_list **l);
void cmd_seven(t_cmd_list **l);
void cmd_eight(t_cmd_list **l);
void cmd_nine(t_cmd_list **l);
void cmd_ten(t_cmd_list **l);
void cmd_eleven(t_cmd_list **l);


void add_input_node(t_cmd_list **lst, char *file);
void add_output_node(t_cmd_list **lst, char *file);

void add_append_output_node(t_cmd_list **lst, char *file);


bool	check_builtin(char *cmd);
// void	run_builtin(t_cmd_list *lst, t_list *env_lst);
void	run_builtin(t_data d, t_cmd_list *lst);


//! env
t_list	*ft_lstnew(void *content);

void list_add_back(t_list **head, t_list *new);



void print_env_lst(t_list *env_lst);

// void add_env(t_list **env_lst, char *env);
void add_env(t_data d, char *env);

// void unset_env(t_list **env_lst, char *env);
void unset_env(t_data d, char *env);

void create_env_lst(char *envp[], t_list **env_lst);

// void	fill_env_file(t_list *env_lst);
void	fill_env_file(t_data d);

char	*get_env(char **envp, char *path);
char	**lst_to_arr(t_list *lst);

#endif