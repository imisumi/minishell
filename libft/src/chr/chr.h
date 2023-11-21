/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chr.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:31:48 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:22:39 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHR_H
# define CHR_H

# include <stdbool.h>

int		ft_isalnum(int arg);
int		ft_isalpha(int arg);
int		ft_isascii(int arg);
int		ft_isdigit(int arg);
int		ft_isprint(int arg);
bool	ft_isspace(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
