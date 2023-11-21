/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:12:27 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:34:14 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Turns char to uppercase
 * @param arg Char to be turned into uppercase
 * @returns New character that is uppercase
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
