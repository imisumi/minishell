/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itob.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 14:19:17 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 17:43:55 by rhorbach      ########   odam.nl         */
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
		n = n / 2;
		counter++;
	}
	return (counter);
}

/**
 * Converts an int to a string, represented as binary
 * @param n The number to be converted
 * @returns The converted string, NULL on error
 */
char	*ft_itob(int n)
{
	char	*ptr;
	int		i;

	i = ft_intlen(n);
	ptr = malloc((i + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	i--;
	while (i != 0)
	{
		ptr[i] = (n % 2) + '0';
		n /= 2;
		i--;
	}
	ptr[i] = (n % 2) + '0';
	return (ptr);
}

// base 10:
// 9265 = 5 * 10^0 + 6 * 10^1 + 2 * 10^2 + 9 * 10^3
// 100011 = 1 * 1   + 1 * 2   + 0 * 4   + 0 * 8   + 0 * 16  + 1 * 32
// 100011 = 1 * 2^0 + 1 * 2^1 + 0 * 2^2 + 0 * 2^3 + 0 * 2^4 + 1 * 2^5
// //35

// 9265 % 10 = 5 //
// 9265 / 10 = 926
// 926 % 10 = 6 //
// 926 / 10 = 92
// 92 % 10 = 2 //
// 92 / 10 = 9
// 9 % 10 = 9 //
// 9 / 10 = 0

// 35 % 2 = 1 //
// 35 / 2 = 17
// 17 % 2 = 1 //
// 17 / 2 = 8
// 8 % 2 = 0 //
// 8 / 2 = 4
// 4 % 2 = 0 //
// 4 / 2 = 2
// 2 % 2 = 0 //
// 2 / 2 = 1
// 1 % 2 = 1 //
// 1 / 2 = 0
