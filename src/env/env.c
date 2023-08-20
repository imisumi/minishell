/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/08/20 19:46:48 by imisumi-wsl      ###   ########.fr       */
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

bool	find_env(t_list *temp, t_list *prev, char *temp_env, t_data d)
{
	if (ft_strncmp((char *)temp->content, temp_env, ft_strlen(temp_env)) == 0)
	{
		printf("found env variable: %s\n", (char *)temp_env);
		if (prev == NULL)
			d.env_lst = temp->next;
		else
			prev->next = temp->next;
		free(temp_env);
		fill_env_file(d);
		return (true);
	}
	return (false);
}

void	unset_env(t_data d, char *env)
{
	t_list	*temp;
	t_list	*prev;
	char	*temp_env;

	if (env[0] == '=')
	{
		printf("= is not a valid env variable\n");
		return ;
	}
	prev = NULL;
	temp_env = ft_strjoin(env, "=");
	temp = d.env_lst;
	while (temp)
	{
		if (find_env(temp, prev, temp_env, d))
			return ;
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

char	**env_paths(char **envp)
{
	int		i;
	char	*env;
	char	*temp;
	char	**paths;

	env = get_env(envp, "PATH=");
	if (env == NULL)
		return (NULL);
	paths = ft_split(env, ':');
	if (!paths)
		exit(1);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = temp;
		i++;
	}
	return (paths);
}

char	**lst_to_arr(t_list *lst)
{
	int		i;
	char	**envp;

	i = ft_lstsize(lst);
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		exit(1);
	i = 0;
	while (lst)
	{
		envp[i] = lst->content;
		i++;
		lst = lst->next;
	}
	envp[i] = NULL;
	return (envp);
}
