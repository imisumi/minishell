/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 17:28:57 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/06/14 18:00:36 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef enum e_gnl {
	GNL_ERROR,
	GNL_EOF,
	GNL_CONTINUE
}	t_gnl;

t_gnl	get_next_line(int fd, char **line_dst);

#endif
