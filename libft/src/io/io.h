/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   io.h                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:32:20 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:43:29 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <unistd.h>
# include <stdbool.h>

ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putendl_fd(char *s, int fd);
ssize_t	ft_puthexnbr_fd(unsigned long n, bool uppercase, int fd);
ssize_t	ft_putnbr_fd(int n, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putunbr_fd(unsigned int n, int fd);

#endif
