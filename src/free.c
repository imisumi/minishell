/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi <imisumi@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:11:45 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 15:01:42 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env_lst(t_list *env_lst)
{
	t_list	*tmp;

	while (env_lst != NULL)
	{
		tmp = env_lst->next;
		free(((t_env *)env_lst->content)->name);
		free(((t_env *)env_lst->content)->value);
		free(((t_env *)env_lst->content));
		free(env_lst);
		env_lst = tmp;
	}
}

void	free_redir_list(t_redir_list *redir)
{
	if (redir == NULL)
		return ;
	free(redir->file);
	free_redir_list(redir->next);
	free(redir);
}

void	free_data_utils(t_data *data)
{
	free(data->utils.local_dir);
	free(data->utils.child_pids);
}

void	free_cmd_lst(t_cmd_list *cmd_list)
{
	t_cmd_list	*current;
	t_cmd_list	*next;

	if (cmd_list == NULL)
		return ;
	current = cmd_list;
	while (current != NULL)
	{
		next = current->next;
		free_2d_array(current->args);
		free_redir_list(current->redir);
		free(current);
		current = next;
	}
}

// void	free_data_cmd(t_data *data)
// {
// 	t_list	*tmp;

// 	while (data->env_lst != NULL)
// 	{
// 		tmp = data->env_lst->next;
// 		free(((t_env *)data->env_lst->content)->name);
// 		free(((t_env *)data->env_lst->content)->value);
// 		free(((t_env *)data->env_lst->content));
// 		free(data->env_lst);
// 		data->env_lst = tmp;
// 	}
// 	free_cmd_lst(data->cmd_list);
// }

// void	free_data_cmd(t_data *data)
// {
// 	t_list	*tmp;

// 	while (data->env_lst != NULL)
// 	{
// 		tmp = data->env_lst->next;
// 		free(((t_env *)data->env_lst->content)->name);
// 		free(((t_env *)data->env_lst->content)->value);
// 		free(((t_env *)data->env_lst->content));
// 		free(data->env_lst);
// 		data->env_lst = tmp;
// 	}
// 	free_cmd_lst(data->cmd_list);
// }

// void	free_child_data(t_data *data, char **envp, char **paths)
// {
// 	free_2d_array(envp);
// 	free_2d_array(paths);
// 	free_data_cmd(data);
// }

// void	free_data_cmd(t_data *data)
// {
// 	free_env_lst(data->env_lst);
// 	free_cmd_lst(data->cmd_list);
// }

// void	free_eof(t_data *data)
// {
// 	free(data->utils.local_dir);
// 	free_env_lst(data->env_lst);
// }
