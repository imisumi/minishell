/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 17:27:39 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:32:49 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks whether the arg is in ascii range
 * @param arg Char to be evaluated
 * @returns 1 if character was within ascii range, 0 if not
 */
int	ft_isascii(int arg)
{
	return (arg >= 0 && arg <= 127);
}
