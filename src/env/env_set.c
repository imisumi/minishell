/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 16:55:19 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/10/02 14:58:42 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "error.h"

static t_error	add_env_var(t_list **env_lst, char *name, char *duped_value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
	{
		free(duped_value);
		return (set_error(E_SYS));
	}
	env->name = ft_strdup(name);
	if (env->name == NULL)
	{
		free(env);
		free(duped_value);
		return (set_error(E_SYS));
	}
	env->value = duped_value;
	if (ft_lstnew_back(env_lst, env) == NULL)
	{
		free(env->name);
		free(env);
		free(duped_value);
		return (set_error(E_SYS));
	}
	return (OK);
}

/**
 * Sets/adds an environment value (old value will be freed)
 * @param env_lst list to be adjusted
 * @param name name of the value to be added (will be duped if necessary)
 * @param value value to be set/added (will be duped)
 */
t_error	set_env_var(t_list **env_lst, char *name, char *value)
{
	char	*duped_value;

	duped_value = NULL;
	if (value != NULL)
	{
		duped_value = ft_strdup(value);
		if (duped_value == NULL)
			return (set_error(E_SYS));
	}
	while (*env_lst != NULL)
	{
		if (ft_strcmp(((t_env *)(*env_lst)->content)->name, name) == 0)
		{
			if (duped_value != NULL)
			{
				free(((t_env *)(*env_lst)->content)->value);
				((t_env *)(*env_lst)->content)->value = duped_value;
			}
			return (OK);
		}
		env_lst = &(*env_lst)->next;
	}
	return (add_env_var(env_lst, name, duped_value));
}

/**
 * Sets/adds an environment value (old value will be freed)
 * @param env_lst list to be adjusted
 * @param env Composite line of the environment (name=value) to be set/added
 */
t_error	set_env_var_composite(t_list **env_lst, char *env)
{
	size_t	j;

	j = 0;
	while (env[j] != '\0' && env[j] != '=')
		j++;
	if (env[j] == '\0')
		return (set_env_var(env_lst, env, NULL));
	env[j] = '\0';
	if (set_env_var(env_lst, env, &env[j + 1]) != OK)
	{
		env[j] = '=';
		return (get_error());
	}
	env[j] = '=';
	return (OK);
}

/**
 * Unsets an enviroment variable
 * @param env_lst list to be adjusted
 * @param name name of variable to unset
 */
void	unset_env_var(t_list **env_lst, char *name)
{
	while (*env_lst != NULL)
	{
		if (ft_strcmp(((t_env *)(*env_lst)->content)->name, name) == 0)
		{
			free(((t_env *)(*env_lst)->content)->name);
			free(((t_env *)(*env_lst)->content)->value);
			free(((t_env *)(*env_lst)->content));
			ft_lst_dispose_one(env_lst, NULL);
			return ;
		}
		env_lst = &(*env_lst)->next;
	}
}
