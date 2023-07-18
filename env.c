#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

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

void print_env_lst(t_list *env_lst)
{
    while (env_lst)
    {
        printf("%s\n", (char *)env_lst->content);
        env_lst = env_lst->next;
    }
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
    temp = calloc(sizeof(char), strlen(env) + 1);
    str_cpy(temp, env);
    new = ft_lstnew(temp);
    list_add_back(env_lst, new);
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
    free(temp_env);
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
        // printf("%s\n", temp);
        new = ft_lstnew(temp);
        // printf("%s\n", (char *)new->content);
        list_add_back(env_lst, new);
        i++;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    t_list *env_lst;

    env_lst = NULL;

    printf("\n");

    create_env_lst(envp, &env_lst);

    add_env(&env_lst, "z=hello");
    add_env(&env_lst, "ff=boo");
    add_env(&env_lst, "d=noob");
    add_env(&env_lst, "asd");

    // print_env_lst(env_lst);

    unset_env(&env_lst, "d");


    // print_env_lst(env_lst);
    // printf("%d\n", i);

    return 0;
}