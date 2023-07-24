#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../include/struct.h"
#include "../include/pipe.h"

void	fill_env_file(t_list *env_lst)
{
	t_list *temp;
	char *temp_env;
	ssize_t bytes_written;
	int	fd;

	fd = open(".env.ms", O_WRONLY | O_CREAT | O_TRUNC, 0666);
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

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->next = NULL;
	new->content = content;
	return (new);
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

// void str_cpy(char *dest, char *src)
// {
// 	int i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// }

void print_env_lst(t_list *env_lst)
{
	while (env_lst)
	{
		printf("%s\n", (char *)env_lst->content);
		env_lst = env_lst->next;
	}
}

void check_existing_env(t_list **env_lst, char *env)
{
	int		i;
	char	*str;

	i = 0;
	while(env[i] && env[i] != '=')
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while(env[i] && env[i] != '=')
	{
		str[i] = env[i];
		i++;
	}
	str[i] = '\0';
	unset_env(env_lst, str);
	free(str);
}


void add_env(t_list **env_lst, char *env)
{
    char *temp;
    t_list *new;

    int i = 0;
    if (strchr(env, '=') == NULL)
    {
        printf("invalid env variable: %s\n", env);
        return ;
    }
	check_existing_env(env_lst, env);
    temp = calloc(sizeof(char), strlen(env) + 1);
    str_cpy(temp, env);
    new = ft_lstnew(temp);
    list_add_back(env_lst, new);
	fill_env_file(*env_lst);
}

void unset_env(t_list **env_lst, char *env)
{
	t_list *temp;
	t_list *prev;

	temp = *env_lst;
	prev = NULL;
	char *temp_env = calloc(sizeof(char), strlen(env) + 2);
	str_cpy(temp_env, env);
	strcat(temp_env, "=");
	while(temp)
	{
		if (strncmp((char *)temp->content, temp_env, strlen(temp_env)) == 0)
		{
			if (prev == NULL)
				*env_lst = temp->next;
			else
				prev->next = temp->next;
			free(temp->content);
			free(temp);
			free(temp_env);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("env variable not found: %s\n", env);
	free(temp);
	free(temp_env);
	fill_env_file(*env_lst);
}

void create_env_lst(char *envp[], t_list **env_lst)
{
    int i;
    char *temp;
    t_list *new;

    i = 0;
    while (envp[i])
    {
        temp = calloc(sizeof(char), strlen(envp[i]) + 1);
        str_cpy(temp, envp[i]);
        new = ft_lstnew(temp);
        list_add_back(env_lst, new);
		// free(temp);
        i++;
    }
	fill_env_file(*env_lst);
}

// int main(int argc, char *argv[], char *envp[])
// {
//     t_list *env_lst;

//     env_lst = NULL;

//     printf("\n");

//     create_env_lst(envp, &env_lst);

//     add_env(&env_lst, "z=hello");
//     add_env(&env_lst, "ff=boo");
//     add_env(&env_lst, "d=noob");
//     add_env(&env_lst, "asd");

//     // print_env_lst(env_lst);

//     unset_env(&env_lst, "d");


//     // print_env_lst(env_lst);
//     // printf("%d\n", i);

//     return 0;
// }