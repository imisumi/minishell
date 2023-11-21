/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/10/19 15:08:10 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	**env_paths(t_list *envp)
{
	int		i;
	char	*env;
	char	*temp;
	char	**paths;

	env = get_env_var_value(envp, "PATH");
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

int	print_env_lst(t_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = (t_env *)env_lst->content;
		if (env->value != NULL)
		{
			ft_putstr_fd(env->name, STDOUT_FILENO);
			write(STDOUT_FILENO, "=", 1);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

static void	print_env_value(t_env *env)
{
	int	i;

	i = 0;
	ft_putstr_fd("\"", STDOUT_FILENO);
	while (env->value[i])
	{
		if (env->value[i] == '\"' || env->value[i] == '$' \
				|| env->value[i] == '\\')
			write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, &env->value[i], 1);
		i++;
	}
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

void	print_export_lst(t_list *env_lst)
{
	t_env	*env;

	while (env_lst)
	{
		env = (t_env *)env_lst->content;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->name, STDOUT_FILENO);
		if (env->value != NULL)
			write(STDOUT_FILENO, "=", 1);
		if (env->value != NULL)
			print_env_value(env);
		else
			write(STDOUT_FILENO, "\n", 1);
		env_lst = env_lst->next;
	}
}

char	**env_list_to_array(t_list *env_list)
{
	char	**envp;
	t_env	*env;
	char	*temp;
	int		i;

	envp = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (env_list)
	{
		env = (t_env *)env_list->content;
		envp[i] = ft_strjoin(env->name, "=");
		if (env->value)
		{
			temp = ft_strjoin(envp[i], env->value);
			free(envp[i]);
			envp[i] = temp;
		}
		i++;
		env_list = env_list->next;
	}
	envp[i] = NULL;
	return (envp);
}
