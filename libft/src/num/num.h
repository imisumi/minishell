/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:33:15 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/05/30 12:46:49 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUM_H
# define NUM_H

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_itob(int n);
char	*ft_itoh(int n);
bool	ft_satoi(const char *str, int *result_ptr);

#endif
