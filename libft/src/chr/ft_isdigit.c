/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:59:47 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:32:47 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks whether the arg is a digit
 * @param arg Char to be evaluated
 * @returns 1 if character was a digit, 0 if not
 */
int	ft_isdigit(int arg)
{
	return (arg >= '0' && arg <= '9');
}
