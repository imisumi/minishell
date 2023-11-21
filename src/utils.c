/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:36:34 by rhorbach          #+#    #+#             */
/*   Updated: 2023/11/16 14:26:09 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*find_path(char *cmd, char **paths)
{
	int		i;
	char	*temp;

	i = 0;
	if (paths == NULL)
		return (cmd);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], cmd);
		free(paths[i]);
		paths[i] = temp;
		if (access(paths[i], F_OK | X_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (cmd);
}

int	fd_put_err(char *input, char *msg, int ret)
{
	if (!TESTING)
		ft_putstr_fd("\033[32;1m", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (input)
		ft_putstr_fd(input, STDERR_FILENO);
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (!TESTING)
		ft_putstr_fd(RESET, STDERR_FILENO);
	return (ret);
}

char	*get_prompt(void)
{
	char	*temp;
	char	*dir;
	char	*ms;

	if (!USE_ASCII_COLOR)
		return (ft_strdup("minishell "));
	dir = getcwd(NULL, 0);
	if (get_exit_code() == 0)
		temp = ft_strjoin(PROMPT_SUCCESS, ft_strrchr(dir, '/') + 1);
	else
		temp = ft_strjoin(PROMPT_FAILURE, ft_strrchr(dir, '/') + 1);
	ms = ft_strjoin(temp, PROMPT_END);
	free(dir);
	free(temp);
	return (ms);
}

t_utils	init_utils(void)
{
	t_utils	utils;
	char	*temp;

	temp = getcwd(NULL, 0);
	utils.local_dir = ft_strjoin(temp, "/.env.ms");
	free(temp);
	return (utils);
}

t_error	set_old_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (set_env_var(&data->env_lst, "OLDPWD", cwd) != OK)
	{
		free(cwd);
		return (get_error());
	}
	free(cwd);
	return (OK);
}
