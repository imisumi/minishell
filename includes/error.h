/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ERROR.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 15:03:25 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/07/28 14:49:01 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "types.h"

t_error	set_error(t_error err);
t_error	get_error(void);
void	print_error(t_error err);

#endif
