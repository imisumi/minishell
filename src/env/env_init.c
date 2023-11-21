/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 16:55:19 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/02 14:52:40 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "error.h"
#include "env.h"

/**
 * Initialises an environment list
 * @param data struct that will soon contain a list of environment variables
 * @param envp array that contains enviroment variables to be initalised
 */
t_error	init_env_lst(t_data *data, char **envp)
{
	size_t	i;

	data->env_lst = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (set_env_var_composite(&data->env_lst, envp[i]) != OK)
			return (get_error());
		i++;
	}
	return (OK);
}
