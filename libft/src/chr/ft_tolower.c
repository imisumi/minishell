/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:12:27 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:33:43 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Turns char to lowercase
 * @param arg Char to be turned into lowercase
 * @returns New character that is lowercase
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
