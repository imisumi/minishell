/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/10/19 14:50:05 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static bool	if_string_n(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (false);
			i++;
		}
	}
	else
		return (false);
	return (true);
}

static bool	echo_n(t_cmd_list *lst)
{
	int	i;

	i = 1;
	while (lst->args[i])
	{
		if (if_string_n(lst->args[i]) == false)
		{
			if (i > 1)
				break ;
			return (false);
		}
		i++;
	}
	if (lst->args[i] == NULL)
		return (true);
	while (lst->args[i])
	{
		ft_putstr_fd(lst->args[i], STDOUT_FILENO);
		if (lst->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	return (true);
}

int	builtin_echo(t_cmd_list *lst)
{
	int	i;

	i = 0;
	if (lst->args[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (echo_n(lst) == true)
		return (0);
	else
	{
		i = 1;
		while (lst->args[i])
		{
			ft_putstr_fd(lst->args[i], STDOUT_FILENO);
			if (lst->args[i + 1])
				write(STDOUT_FILENO, " ", 1);
			else
				write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
	return (0);
}

static int	builtin_cd_2(t_data *d, char *cwd)
{
	if (get_env_var_value(d->env_lst, "OLDPWD") != NULL)
		set_env_var(&d->env_lst, "OLDPWD", cwd);
	free(cwd);
	if (get_env_var_value(d->env_lst, "PWD") != NULL)
	{
		cwd = getcwd(NULL, 0);
		set_env_var(&d->env_lst, "PWD", cwd);
		free(cwd);
	}
	return (0);
}

int	builtin_cd(t_data *d, t_cmd_list *lst)
{
	char	*cwd;
	int		check;
	char	*home;

	if (lst->args[1] && lst->args[2])
		return (fd_put_err("cd: too many arguments\n", NULL, 1));
	cwd = getcwd(NULL, 0);
	if (lst->args[1] == NULL)
	{
		home = get_env_var_value(d->env_lst, "HOME");
		if (home == NULL)
			return (free(cwd), fd_put_err("cd: HOME not set\n", NULL, 1));
		check = chdir(home);
	}
	else
		check = chdir(lst->args[1]);
	if (check == -1)
	{
		free(cwd);
		cwd = ft_strjoin("cd: ", lst->args[1]);
		fd_put_err(cwd, ": No such file or directory\n", 1);
		return (free(cwd), 1);
	}
	return (builtin_cd_2(d, cwd));
}
