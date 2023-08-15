

#include "../include/pipe.h"

void temp_cmd(t_cmd_list **lst, char *cmd, char **args)
{
	*lst = create_cmd_list(cmd, args);
}

void temp_cmd_pipe(t_cmd_list **lst, char **arg1, char **arg2)
{
	*lst = create_cmd_list(arg1[0], arg1);

	t_cmd_list *new_cmd = create_cmd_list(arg2[0], arg2);
	cmd_list_add_back(lst, new_cmd);
}
