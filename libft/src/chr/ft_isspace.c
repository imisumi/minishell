/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 17:08:18 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:32:40 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * Checks whether the arg is a whitespace
 * @param arg Char to be evaluated
 * @returns 1 if character was a whitespace, 0 if not
 */
bool	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
