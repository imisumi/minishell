/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_get.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 16:55:19 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 14:30:09 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "error.h"
#include "pipe.h"

/**
 * Retrieves an enviroment variable
 * @param env_lst list to look through
 * @param name name of variable to find
 * @returns The enviroment variable, NULL if not found
 */
t_env	*get_env_var(t_list *env_lst, char *name)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(((t_env *)(env_lst)->content)->name, name) == 0)
			return (((t_env *)(env_lst)->content));
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*get_env_var_value(t_list *env_lst, char *name)
{
	while (env_lst != NULL)
	{
		if (ft_strcmp(((t_env *)(env_lst)->content)->name, name) == 0)
			return (((t_env *)(env_lst)->content)->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

/**
 * Retrieves an enviroment variable of length n
 * @param env_lst list to look through
 * @param name name of variable to find
 * @param n The maximum number of characters to compare
 * @returns The enviroment variable, NULL if not found
 */
t_env	*get_env_var_n(t_list *env_lst, char *name, size_t n)
{
	while (env_lst != NULL)
	{
		if (ft_strncmp(((t_env *)(env_lst)->content)->name, name, n) == 0 \
		&& ((t_env *)(env_lst)->content)->name[n] == '\0')
			return (((t_env *)(env_lst)->content));
		env_lst = env_lst->next;
	}
	return (NULL);
}

// void	fill_env_file(t_data d)
// {
// 	t_list	*temp;
// 	ssize_t	bytes_written;
// 	int		fd;
// 	t_env	*env;

// 	fd = open(d.utils.local_dir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return ;
// 	temp = d.env_lst;
// 	while (temp)
// 	{
// 		env = (t_env *)temp->content;
// 		bytes_written = ft_putstr_fd(env->name, fd);
// 		if (env->value)
// 		{
// 			bytes_written = ft_putstr_fd("=", fd);
// 			bytes_written = ft_putstr_fd(env->value, fd);
// 		}
// 		bytes_written = ft_putstr_fd("\n", fd);
// 		if (bytes_written == -1)
// 			return ;
// 		temp = temp->next;
// 	}
// 	close(fd);
// }
