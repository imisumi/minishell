/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi <imisumi@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:11:45 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 14:17:01 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	free_data_cmd(t_data *data)
{
	free_env_lst(data->env_lst);
	free_cmd_lst(data->cmd_list);
}

void	free_child_data(t_data *data, char **envp, char **paths)
{
	free_2d_array(envp);
	free_2d_array(paths);
	free_data_cmd(data);
}

void	free_eof(t_data *data)
{
	free(data->utils.local_dir);
	free_env_lst(data->env_lst);
}

void	free_data(t_data *data)
{
	free_env_lst(data->env_lst);
	free(data->utils.local_dir);
}

t_error	clean_input(t_data *data, char *prompt)
{
	free_eof(data);
	free(prompt);
	rl_clear_history();
	return (OK);
}
