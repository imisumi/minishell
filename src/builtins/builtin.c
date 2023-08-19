/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/20 00:58:17 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipe.h"

bool	str_cmp(char *s1, char *s2)
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
				printf("%s ", lst->args[i]);
			else
				printf("%s\n", lst->args[i]);
			i++;
		}
	}
}

void	builtin_unset(t_data d)
{
	unset_env(d, d.cmd_list->args[1]);
}


void	builtin_export(t_data d)
{
	add_env(d, d.cmd_list->args[1]);
}

void	builtin_cd(t_data d)
{
	char	*cwd;
	char	*temp;
	int		check;

	check = 0;
	cwd = getcwd(NULL, 0);
	if (d.cmd_list->args[1] == NULL)
		check = chdir(get_env(lst_to_arr(d.env_lst), "HOME="));
	else
		check = chdir(d.cmd_list->args[1]);
	if (check == -1)
		return ;
	if (get_env(lst_to_arr(d.env_lst), "OLDPWD=") != NULL)
	{
		temp = ft_strjoin("OLDPWD=", cwd);
		add_env(d, temp);
		free(temp);
	}
	free(cwd);
	if (get_env(lst_to_arr(d.env_lst), "PWD=") != NULL)
	{
		cwd = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", cwd);
		add_env(d, temp);
		free(temp);
		free(cwd);
	}
}

void run_builtin(t_data d)
{
	char	*cwd;
	if (strcmp(d.cmd_list->cmd, "pwd") == 0)
	{
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
		free(cwd);
	}
	if (strcmp(d.cmd_list->cmd, "echo") == 0)
		builtin_echo(d.cmd_list);
	if (strcmp(d.cmd_list->cmd, "env") == 0)
		print_env_lst(d.env_lst);
	if (strcmp(d.cmd_list->cmd, "unset") == 0)
		builtin_unset(d);
	if (strcmp(d.cmd_list->cmd, "export") == 0)
		builtin_export(d);
	if (strcmp(d.cmd_list->cmd, "cd") == 0)
		builtin_cd(d);
	// if (strcmp(d.cmd_list->cmd, "exit") == 0)
	// 	exit(0);
}
