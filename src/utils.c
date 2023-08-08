/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/07 14:33:10 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipe.h"

void str_cpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

uint32_t list_size(t_cmd_list *list)
{
	uint32_t size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

t_cmd_list *create_cmd_list(char *cmd, char **args)
{
	t_cmd_list *cmd_list;

	cmd_list = calloc(sizeof(t_cmd_list), 1);
	// cmd_list->cmd = calloc(sizeof(char), strlen(cmd) + 1);
	// str_cpy(cmd_list->cmd, cmd);
	cmd_list->cmd = ft_strdup(cmd);

	cmd_list->args = calloc(sizeof(char *), 10);
	for (int i = 0; args[i]; i++)
	{
		// cmd_list->args[i] = calloc(sizeof(char), 10);
		// str_cpy(cmd_list->args[i], args[i]);
		cmd_list->args[i] = ft_strdup(args[i]);
	}
	cmd_list->next = NULL;
	cmd_list->redir = NULL;
	return (cmd_list);
}

void	add_back(t_cmd_list **list, t_cmd_list *new)
{
	t_cmd_list *temp;

	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	// return (list);
}

void print_args(t_cmd_list *lst)
{
	int i;
	t_cmd_list *temp = lst;
	while(temp)
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
	// printf("check\n");
}

//! redir utils

void add_input_node(t_cmd_list **lst, char *file)
{
	t_redir *new = new_redir_node();
	str_cpy(new->file, file);
	new->type = REDIR_INPUT;
	redir_add_back(lst, new);
}

void add_output_node(t_cmd_list **lst, char *file)
{
	t_redir *new = new_redir_node();
	str_cpy(new->file, file);
	new->type = REDIR_OUTPUT;
	redir_add_back(lst, new);
}

void add_pipe_node(t_cmd_list **lst)
{
	t_redir *new = new_redir_node();
	new->type = REDIR_PIPE;
	new->file = NULL;
	redir_add_back(lst, new);
}

void add_append_output_node(t_cmd_list **lst, char *file)
{
	t_redir *new = new_redir_node();
	str_cpy(new->file, file);
	new->type = REDIR_OUTPUT_APPEND;
	redir_add_back(lst, new);
}