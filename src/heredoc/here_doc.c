/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:18 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/23 16:07:18 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "pipe.h"

static char	*line_expander(char *line, t_list *env_list)
{
	char	*ref;

	if (line == NULL)
		return (NULL);
	while (true)
	{
		if (!line)
			break ;
		ref = ft_strdup(line);
		if (ref == NULL)
			return (free(line), NULL);
		line = expand_line(line, env_list);
		if (line == NULL)
			return (free(ref), free(line), NULL);
		if (ft_strcmp(line, ref) == 0)
		{
			free(ref);
			break ;
		}
	}
	return (line);
}

int	storage(int value, int flag)
{
	static int	saved_value = 0;

	if (flag == SET)
		saved_value = value;
	else if (flag == GET)
		return (saved_value);
	return (0);
}

static bool	here_doc_input(t_data *data, char *heredoc, int fd)
{
	char	*line;

	while (true)
	{
		if (storage(0, GET) == 1)
			return (false);
		line = readline(HERE_DOC);
		if (line == NULL)
			return (false);
		if (storage(0, GET) == 1)
			return (free(line), false);
		if (ft_strcmp(line, heredoc) == 0 || line == NULL)
		{
			free(line);
			break ;
		}
		line = line_expander(line, data->env_lst);
		if (line == NULL)
			return (false);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	return (true);
}

// bool	here_doc(t_data *data, char *heredoc)
// {
// 	int		fd;
// 	char	*temp;
// 	char	*file;

// 	temp = generate_random_numbers(10);
// 	file = ft_strjoin(HERE_DOC_TMP, temp);
// 	free(temp);
// 	dup2(data->utils.fd[2], STDIN_FILENO);
// 	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (!fd)
// 		return (false);
// 	if (here_doc_input(data, heredoc, fd) == true)
// 	{
// 		close(fd);
// 		fd = open(file, O_RDONLY);
// 		if (!fd)
// 			ft_putstr_fd("here_doc: open error\n", 1);
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		return (unlink(file), free(file), true);
// 	}
// 	close(fd);
// 	return (unlink(file), free(file), false);
// }

bool	here_doc(t_data *data, char *heredoc)
{
	int			fd;
	char		*temp;
	char		*file;
	static int	num = 1;

	temp = ft_itoa(num++);
	if (!temp)
		return (false);
	file = ft_strjoin(HERE_DOC_TMP, temp);
	if (!file)
		return (free(temp), false);
	dup2(data->utils.fd[2], STDIN_FILENO);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!fd)
		return (free(temp), free(file), false);
	if (here_doc_input(data, heredoc, fd) == true)
	{
		close(fd);
		fd = open(file, O_RDONLY);
		if (!fd)
			ft_putstr_fd("here_doc: open error\n", 1);
		dup2(fd, STDIN_FILENO);
		return (free(temp), close(fd), unlink(file), free(file), true);
	}
	return (free(temp), close(fd), unlink(file), free(file), false);
}
