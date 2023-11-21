/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 17:28:55 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:35:30 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_int.h"

static char	*append_buffer(char **line_ptr, char *buffer, int buffer_len)
{
	int		line_len;
	char	*dst;

	line_len = ft_strlen(*line_ptr);
	dst = malloc((buffer_len + line_len + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_memmove(dst, *line_ptr, line_len);
	ft_memmove(&dst[line_len], buffer, buffer_len);
	dst[buffer_len + line_len] = '\0';
	free(*line_ptr);
	*line_ptr = dst;
	return (*line_ptr);
}

static t_nl_found	pass_new_line(char *temp, char **line_ptr,
	char *line_part, ssize_t part_len)
{
	int		i;

	i = 0;
	while (i < part_len && line_part[i] != '\n')
		i++;
	if (i < part_len)
	{
		ft_memmove(temp, &line_part[i + 1], part_len - i - 1);
		temp[part_len - i - 1] = '\0';
		if (append_buffer(line_ptr, line_part, i + 1) == NULL)
			return (ERROR);
		return (NL_FOUND);
	}
	if (append_buffer(line_ptr, line_part, part_len) == NULL)
		return (ERROR);
	temp[0] = '\0';
	return (NL_NOT_FOUND);
}

/**
 * Gets the next line from the file pointed to by fd
 * @param fd file descriptor to read from
 * @param line_dst address that will receive output line
 * @return GNL_CONTINUE when line was found,
 * GNL_EOF when EOF was found (no line),
 * GNL_ERROR on error
*/
t_gnl	get_next_line(int fd, char **line_dst)
{
	static char	temp[BUFFER_SIZE];
	char		buffer[BUFFER_SIZE];
	char		*line;
	t_nl_found	nl_found;
	ssize_t		buffer_bytes;

	line = empty_string();
	if (line == NULL)
		return (GNL_ERROR);
	buffer_bytes = ft_strlen(temp);
	ft_memmove(buffer, temp, buffer_bytes);
	while (buffer_bytes != -1)
	{
		nl_found = pass_new_line(temp, &line, buffer, buffer_bytes);
		if (nl_found == ERROR)
			return (clear(line, GNL_ERROR));
		if (nl_found == NL_FOUND)
			return (return_line(line, line_dst));
		buffer_bytes = read(fd, buffer, BUFFER_SIZE);
		if (buffer_bytes == 0 && line[0] == '\0')
			return (clear(line, GNL_EOF));
		if (buffer_bytes == 0)
			return (return_line(line, line_dst));
	}
	return (clear(line, GNL_ERROR));
}
