/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/15 15:12:43 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipe.h"

void	fill_env_file(t_data d)
{
	t_list	*temp;
	char	*temp_env;
	ssize_t	bytes_written;
	int		fd;

	fd = open(d.utils.local_dir, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		printf("error opening file\n");
		exit(1);
	}
	temp = d.env_lst;
	while (temp)
	{
		temp_env = (char *)temp->content;
		bytes_written = write(fd, temp_env, ft_strlen(temp_env));
		if (bytes_written == -1)
		{
			printf("error writing to file\n");
			exit(1);
		}
		bytes_written = write(fd, "\n", 1);
		if (bytes_written == -1)
		{
			printf("error writing to file\n");
			exit(1);
		}
		temp = temp->next;
	}
	close(fd);
}

void	print_env_lst(t_list *env_lst)
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

	i = 0;
	while (env[i] != '=')
		i++;
	str = ft_substr(env, 0, i);
	if (!str)
		exit(1);
	unset_env(d, str);
	free(str);
}

void	add_env(t_data d, char *env)
{
	char	*temp;
	t_list	*new;

	if (ft_strchr(env, '=') == NULL || env[0] == '=')
	{
		printf("invalid env variable: %s\n", env);
		return ;
	}
	check_existing_env(d, env);
	temp = strdup(env);
	new = ft_lstnew(temp);
	ft_lstadd_back(&d.env_lst, new);
	fill_env_file(d);
}

void	unset_env(t_data d, char *env)
{
	t_list	*temp;
	t_list	*prev;
	char	*temp_env;
	t_list	**env_lst;

	env_lst = &d.env_lst;
	if (env[0] == '=')
	{
		printf("= is not a valid env variable\n");
		return ;
	}
	prev = NULL;
	temp_env = ft_strjoin(env, "=");
	temp = *env_lst;
	while (temp)
	{
		if (ft_strncmp((char *)temp->content, temp_env, \
			ft_strlen(temp_env)) == 0)
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
}

char	*get_env(char **envp, char *path)
{
	int		i;
	char	*env;

	i = 0;
	while (envp[i])
	{
		env = ft_strnstr(envp[i], path, ft_strlen(path));
		if (env != NULL)
		{
			env = env + ft_strlen(path);
			return (env);
		}
		i++;
	}
	return (NULL);
}
