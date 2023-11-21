/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/10/19 14:52:14 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static bool	is_numberic(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(t_cmd_list *lst, bool printf_exit)
{
	char	*temp;

	if (printf_exit == true && !TESTING)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (lst->args[1] == NULL)
		return (get_exit_code());
	if (lst->args[1] != NULL)
	{
		if (is_numberic(lst->args[1]) == false)
		{
			temp = ft_strjoin("exit: ", lst->args[1]);
			fd_put_err(temp, ": numeric argument required\n", 255);
			return (free(temp), 2);
		}
	}
	if (lst->args[1] != NULL && lst->args[2] == NULL)
		return (ft_atoi(lst->args[1]));
	if (lst->args[1] != NULL && lst->args[2] != NULL)
		fd_put_err("exit", ": too many arguments\n", 1);
	return (get_exit_code());
}
