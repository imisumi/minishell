/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_satoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:44:37 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:46:54 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

/**
 * Converts a string to an int, very strictly
 * @param str The string to be converted
 * @param result_ptr A pointer to store the resulting int in
 * @returns A boolean indicating whether the conversion was succesfull
 */
bool	ft_satoi(const char *str, int *result_ptr)
{
	int		i;
	int		sign;
	long	c;

	sign = -1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (false);
	c = 0;
	while (ft_isdigit(str[i]))
	{
		c = ((c * 10) - (str[i] - '0'));
		if (c * sign < -2147483648 || c * sign > 2147483647)
			return (false);
		i++;
	}
	*result_ptr = c * sign;
	return (str[i] == '\0');
}
