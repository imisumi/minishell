/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 18:02:20 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/06/14 18:04:27 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_int.h"

t_gnl	clear(char *line, t_gnl return_value)
{
	free(line);
	return (return_value);
}

t_gnl	return_line(char *line, char **line_dst)
{
	*line_dst = line;
	return (GNL_CONTINUE);
}

char	*empty_string(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}
