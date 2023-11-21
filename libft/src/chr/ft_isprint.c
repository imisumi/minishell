/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:31:24 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:32:45 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks whether the arg is within printable range
 * @param arg Char to be evaluated
 * @returns 1 if character was within printable range, 0 if not
 */
int	ft_isprint(int arg)
{
	return (arg >= 32 && arg <= 126);
}
