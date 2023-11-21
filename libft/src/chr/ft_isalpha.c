/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 14:57:07 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:32:51 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks whether the arg is a letter
 * @param arg Char to be evaluated
 * @returns 1 if character was a letter, 0 if not
 */
int	ft_isalpha(int arg)
{
	return ((arg >= 'A' && arg <= 'Z') || (arg >= 'a' && arg <= 'z'));
}
