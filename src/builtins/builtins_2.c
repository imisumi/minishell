/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/10/19 14:48:05 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static bool	valid_export_identifier(char *arg)
{
	char	*temp;
	int		i;

	if (arg[0] == '=' || ft_isdigit(arg[0]) == 1)
	{
		temp = ft_strjoin("export: `", arg);
		fd_put_err(temp, "': not a valid identifier\n", 1);
		return (free(temp), false);
	}
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (true);
		if (arg[i] == '_' || ft_isalnum(arg[i]) == 1)
			i++;
		else
		{
			temp = ft_strjoin("export: `", arg);
			fd_put_err(temp, "': not a valid identifier\n", 1);
			return (free(temp), false);
		}
	}
	return (true);
}

// int i && exit_code for norm
static int	export_variables(t_data *data, t_cmd_list *lst, int i, int exitcode)
{
	int		j;

	while (lst->args[i])
	{
		if (valid_export_identifier(lst->args[i]) == true)
		{
			if (ft_strchr(lst->args[i], '=') == NULL && i != 0)
				set_env_var(&data->env_lst, lst->args[i], NULL);
			else
			{
				j = 0;
				while (lst->args[i][j] != '=')
					j++;
				if (lst->args[i][j] == '\0')
					set_env_var(&data->env_lst, lst->args[i], "");
				else
					set_env_var_composite(&data->env_lst, lst->args[i]);
			}
		}
		else
			exitcode = 1;
		i++;
	}
	return (exitcode);
}

int	builtin_export(t_data *data, t_cmd_list *lst)
{
	if (lst->args[1] == NULL)
		return (print_export_lst(data->env_lst), 0);
	return (export_variables(data, lst, 1, 0));
}

int	builtin_unset(t_data *data, t_cmd_list *lst)
{
	int		i;
	char	**args;

	args = lst->args;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		unset_env_var(&data->env_lst, args[i]);
		i++;
	}
	return (0);
}
