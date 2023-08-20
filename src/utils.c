/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/20 19:46:01 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe.h"

int	cmd_list_size(t_cmd_list *list)
{
	int	size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

t_cmd_list	*create_cmd_list(char *cmd, char **args)
{
	int			i;
	t_cmd_list	*cmd_list;

	cmd_list = calloc(sizeof(t_cmd_list), 1);
	cmd_list->cmd = ft_strdup(cmd);
	cmd_list->args = calloc(sizeof(char *), 10);
	i = 0;
	while (args[i])
	{
		cmd_list->args[i] = ft_strdup(args[i]);
		i++;
	}
	cmd_list->next = NULL;
	cmd_list->redir = NULL;
	return (cmd_list);
}

void	cmd_list_add_back(t_cmd_list **list, t_cmd_list *new)
{
	t_cmd_list	*temp;

	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	print_args(t_cmd_list *lst)
{
	int			i;
	t_cmd_list	*temp;

	temp = lst;
	while (temp)
	{
		printf("%s\n", temp->cmd);
		i = 0;
		while (temp->args[i])
		{
			printf("%s ", temp->args[i]);
			i++;
		}
		temp = temp->next;
		printf("\n");
	}
	printf("\n");
}

void	add_input_node(t_cmd_list **lst, char *file)
{
	t_redir	*new;

	new = redir_new_node();
	new->file = ft_strdup(file);
	new->type = REDIR_INPUT;
	redir_add_back(lst, new);
}

void	add_output_node(t_cmd_list **lst, char *file)
{
	t_redir	*new;

	new = redir_new_node();
	new->file = ft_strdup(file);
	new->type = REDIR_OUTPUT;
	redir_add_back(lst, new);
}

void	add_append_output_node(t_cmd_list **lst, char *file)
{
	t_redir	*new;

	new = redir_new_node();
	new->file = ft_strdup(file);
	new->type = REDIR_OUTPUT_APPEND;
	redir_add_back(lst, new);
}
