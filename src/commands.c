

#include "../include/pipe.h"


//! single command
void cmd_one(t_cmd_list **lst)
{
	// *lst = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
	*lst = create_cmd_list("/bin/ls", (char *[]){"ls", NULL});
}

void cmd_two(t_cmd_list **lst)
{
	*lst = create_cmd_list("/usr/bin/grep", (char *[]){"grep", "a", NULL});

	add_input_node(lst, "Makefile");
	add_output_node(lst, "out");
}

void cmd_three(t_cmd_list **lst)
{
	*lst = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
	add_pipe_node(lst);

	t_cmd_list *new_cmd = create_cmd_list("/usr/bin/tail", (char *[]){"tail", "-1", NULL});
	add_output_node(&new_cmd, "out");

	add_back(lst, new_cmd);
}

void cmd_four(t_cmd_list **lst)
{
	*lst = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
	add_pipe_node(lst);

	t_cmd_list *new_cmd = create_cmd_list("/usr/bin/grep", (char *[]){"grep", "d", NULL});
	add_pipe_node(&new_cmd);
	add_back(lst, new_cmd);

	new_cmd = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
	add_output_node(&new_cmd, "out");
	add_back(lst, new_cmd);

}

//! ls -la | grep d | ls -la > out | ls
void cmd_five(t_cmd_list **lst)
{
	*lst = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
	add_pipe_node(lst);

	t_cmd_list *new_cmd = create_cmd_list("/usr/bin/grep", (char *[]){"grep", "d", NULL});
	add_pipe_node(&new_cmd);
	add_back(lst, new_cmd);

	new_cmd = create_cmd_list("/bin/ls", (char *[]){"ls", "-la", NULL});
	add_output_node(&new_cmd, "out");
	add_pipe_node(&new_cmd);
	add_back(lst, new_cmd);

	new_cmd = create_cmd_list("/bin/ls", (char *[]){"ls", NULL});
	// add_output_node(&new_cmd, "out");
	add_back(lst, new_cmd);
}

void cmd_six(t_cmd_list **lst)
{
	*lst = create_cmd_list("/bin/echo", (char *[]){"echo", "hey", NULL});
	add_append_output_node(lst, "out");
}

void cmd_seven(t_cmd_list **lst)
{
	// *lst = create_cmd_list("echo", (char *[]){"echo", "-n", "hello world", NULL});
	// *lst = create_cmd_list("echo", (char *[]){"echo", "-n", NULL});

	*lst = create_cmd_list("echo", (char *[]){"echo", "hello world", NULL});
	t_cmd_list *new_cmd = create_cmd_list("echo", (char *[]){"echo", "-n", "yooooooo",NULL});
	add_back(lst, new_cmd);
}

void cmd_eight(t_cmd_list **lst)
{

}

void cmd_nine(t_cmd_list **lst)
{

}

void cmd_ten(t_cmd_list **lst)
{

}