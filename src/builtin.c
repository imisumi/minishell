
#include "../include/pipe.h"


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

void	builtin_echo(t_cmd_list *lst)
{
	int	i;

	i = 0;
	if (str_cmp(lst->args[1], "-n") == true)
	{
		if (lst->args[2] == NULL)
			return ;
		i = 2;
		while (lst->args[i])
		{
			if (lst->args[i + 1])
				printf("%s ", lst->args[i]);
			else
				printf("%s ", lst->args[i]);
			i++;
		}
	}
	else
	{
		if (lst->args[1] == NULL)
			return ;
		i = 1;
		while (lst->args[i])
		{
			if (lst->args[i + 1])
				printf("%s ", lst->args[2]);
			else
				printf("%s\n", lst->args[2]);
			i++;
		}
	}
}

void	builtin_unset(t_cmd_list *lst, t_list *env_lst)
{
	unset_env(&env_lst, lst->args[1]);
}

void	builtin_export(t_cmd_list *lst, t_list *env_lst)
{
	add_env(&env_lst, lst->args[1]);
}

void	builtin_cd(t_cmd_list *lst)
{
	//TODO: own get env
	if (lst->args[1] == NULL) {
		// printf("cd: HOME not set\n");
		chdir(getenv("HOME"));
	}
	else
		chdir(lst->args[1]);
}

void run_builtin(t_cmd_list *lst, t_list *env_lst)
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
		builtin_echo(lst);
	if (strcmp(lst->cmd, "env") == 0)
		print_env_lst(env_lst);
	if (strcmp(lst->cmd, "unset") == 0)
		builtin_unset(lst, env_lst);
	if (strcmp(lst->cmd, "export") == 0)
		builtin_export(lst, env_lst);
	if (strcmp(lst->cmd, "cd") == 0)
		builtin_cd(lst);
}