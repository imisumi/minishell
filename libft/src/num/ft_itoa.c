/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 12:37:15 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:43:23 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_intlen(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

/**
 * Converts an int to a string
 * @param n The number to be converted
 * @returns The converted string, NULL on error
 */
char	*ft_itoa(int n)
{
	char	*ptr;
	int		sign;
	int		i;

	i = ft_intlen(n);
	sign = 1;
	ptr = malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[i--] = '\0';
	if (n < 0)
		sign *= -1;
	while (i != 0)
	{
		ptr[i] = sign * (n % 10) + '0';
		n /= 10;
		i--;
	}
	if (sign == 1)
		ptr[i] = (n % 10) + '0';
	else
		ptr[i] = '-';
	return (ptr);
}
