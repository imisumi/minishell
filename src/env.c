#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../include/struct.h"
#include "../include/pipe.h"

void	fill_env_file(t_data d)
{
	t_list *temp;
	char *temp_env;
	ssize_t bytes_written;
	int	fd;
	t_list *env_lst = d.env_lst;

	fd = open(d.utils.local_dir, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		printf("error opening file\n");
		exit(1);
	}
	temp = env_lst;
	while (temp)
	{
		temp_env = (char *)temp->content;
		bytes_written = write(fd, temp_env, strlen(temp_env));
		bytes_written = write(fd, "\n", 1);
		temp = temp->next;
	}
	close(fd);
}

void list_add_back(t_list **head, t_list *new)
{
	t_list *temp;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void print_env_lst(t_list *env_lst)
{
	while (env_lst)
	{
		printf("%s\n", (char *)env_lst->content);
		env_lst = env_lst->next;
	}
}

void	check_existing_env(t_data d, char *env)
{
	int		i;
	char	*str;
	t_list **env_lst = &d.env_lst;

	i = 0;
	while(env[i] != '=')
		i++;
	str = ft_substr(env, 0, i);
	if (!str)
		exit(1);
	unset_env(d, str);
	free(str);
}

void add_env(t_data d, char *env)
{
	char	*temp;
	t_list	*new;
	t_list **env_lst = &d.env_lst;

	if (ft_strchr(env, '=') == NULL || env[0] == '=')
	{
		printf("invalid env variable: %s\n", env);
		return ;
	}
	// add_check_utils(&d.utils, env);
	// printf("adding env: %s\n", env);
	check_existing_env(d, env);
	temp = strdup(env);
	new = ft_lstnew(temp);
	ft_lstadd_back(env_lst, new);
	fill_env_file(d);
}

void	unset_env(t_data d, char *env)
{
	t_list	*temp;
	t_list	*prev;
	char	*temp_env;

	t_list **env_lst = &d.env_lst;
	if (env[0] == '=')
	{
		printf("= is not a valid env variable\n");
		return ;
	}
	// unset_check_utils(d.utils, env);
	prev = NULL;
	temp_env = ft_strjoin(env, "=");
	temp = *env_lst;
	while(temp)
	{
		if (ft_strncmp((char *)temp->content, temp_env, ft_strlen(temp_env)) == 0)
		{
			printf("found env variable: %s\n", (char *)temp_env);
			if (prev == NULL)
				*env_lst = temp->next;
			else
				prev->next = temp->next;
			free(temp_env);
			fill_env_file(d);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	free(temp_env);
	fill_env_file(d);
}


void	init_env_lst(t_data *d, char **envp)
{
	t_list	*env_lst;
	t_list	*temp;
	char	*temp_env;
	int		i;

	i = 0;
	env_lst = NULL;
	while (envp[i])
	{
		temp_env = ft_strdup(envp[i]);
		if (!temp_env)
			exit(1);
		temp = ft_lstnew(temp_env);
		if (!temp)
			exit(1);
		ft_lstadd_back(&env_lst, temp);
		i++;
	}
	d->env_lst = env_lst;
	fill_env_file(*d);
	// return (env_lst);
}
